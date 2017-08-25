/*
 * This file is used to define generic utilities for the project
 *
 * Contains: 
 *   program version constant
 *   program options and their help messages
 *   render settings struct and other stuffs surrounding it
 *   ascii art!
 */

#ifndef _OPTS_H
#define _OPTS_H

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <getopt.h>
#include <math.h>
#include <string.h>

// local includes
#include "resolutions.h"
#include "colors.h"

#define PROGRAM_VERSION        0.1
#define NUM_COMMANDS            10
#define ASCII_LINES              9
#define DEFAULT_ZOOM           0.5
#define DEFAULT_RE            -0.7
#define DEFAULT_IM             0.0

// define macros for random value creation
#define RAND_ZOOM_HIGH        10.0

#define RANDOM(LOW, HIGH) (LOW + (rand() * (HIGH - LOW)))

/*
 * Some ascii art to print at the help page
 */
static const char* ascii_art[ASCII_LINES] =
{
    "                  .      ",
    "               ..***.    ",
    "        .    .*******.   ",
    "    .  .*.  .********.   ",
    "   .*..***..********.    ",
    "    .  .*.  .********.   ",
    "        .    .*******.   ",
    "               ..***.    ",
    "                  .      ",
};


/*
 * getopt_long arguments
 * 0 - no_arg, 1 - mandatory, 2 - arg required
 */
static struct option long_opts[NUM_COMMANDS] =
{
    {"size",    2,    0, 's'},
    {"real",    2,    0, 'x'},
    {"imag",    2,    0, 'y'},
    {"output",  2,    0, 'o'},
    {"colors",  2,    0, 'c'},
    {"zoom",    2,    0, 'z'},
    {"random",  0,    0, 'r'},
    {"verbose", 0,    0, 'v'},
    {"help",    0,    0, 'h'},
    {NULL,      0, NULL,   0}
};


/*
 * help messages for each command
 */
static const char* option_help[NUM_COMMANDS] =
{
    "sets the target resolution of the render",
    "sets the initial real value to use",
    "sets the initial imaginary value to use",
    "tell the program what name to use for the output file",
    "informs the program what color map to use",
    "sets the zoom level",
    "selects random coordinates and magnification",
    "the program will display more text during runtime",
    "shows this help screen",
    "",
};

/*
 * The Settings class to pass through to render functions
 * Will contain all data about the image type and dimensions
 */
class Settings
{
public:
    uint8_t   verbose;
    uint8_t   random;
    double    init_real;
    double    init_imag;
    double    zoom;
    // char* fname;
    reso_t*   res;
    Gradient* grad;

    double span_x;
    double span_y;
    double topleft_x;
    double topleft_y;
    double botright_x;
    double botright_y;

    double inc_re;
    double inc_im;

    // constructor - do all the dimensional alignment/math here
    Settings(uint8_t v, uint8_t r, double ir, double ii, double z,
             reso_t* out, colormap_t* map)
    {
        verbose   =   v;
        random    =   r;

        // if we're in random mode, generate coordinates randomly
        if(!random)
        {
            init_real =  ir;
            init_imag =  ii;
            zoom      =   z;
        }
        else
        {
            unsigned int a0 = RANDOM(0, 2*M_PI);
            unsigned int a1 = RANDOM(0, 2*M_PI);
            init_real       = (double)sin(a0);
            init_imag       = (double)cos(a1);
            zoom            = (double)fabs(sin(a0+a1)) * RAND_ZOOM_HIGH;
        }
        res      = out;
        grad     = new Gradient(map->color1, map->color2);

        double w = double(res->width);
        double h = double(res->height);
        span_x   = ((w/h) * 0.5) * (1.0 / zoom);
        span_y   =          0.5  * (1.0 / zoom);

        topleft_x  = init_real - span_x;
        topleft_y  = init_imag - span_y;
        botright_x = init_real + span_x;
        botright_y = init_imag + span_y;

        inc_re = (fabs(topleft_x - botright_x)) * (1.0 / w);
        inc_im = (fabs(topleft_y - botright_y)) * (1.0 / h);
    }

    /*
     * Displays info about the fractal space when verbosity is set
     */
    void display_info()
    {
        if(!verbose)
            return;

        // print some basic stuff
        if(random)
            std::cout << "*** Random mode enabled! ***" << std::endl;

        std::cout << "Target resolution: " << res->width << "x"  << res->height << std::endl;
        std::cout << "Desired point:     " <<  init_real << "x " <<   init_imag << std::endl;
        std::cout << "Spans:             " <<     span_x << "x " <<      span_y << std::endl;
        std::cout << "Top left:          " <<  topleft_x << "x " <<   topleft_y << std::endl;
        std::cout << "Bot right:         " << botright_x << "x " <<  botright_y << std::endl;
        std::cout << "Increments:        " <<     inc_re << "x " <<      inc_im << std::endl;
        std::cout << "Magnification:     " <<       zoom <<                        std::endl;
    };
};

/*
 * Prints all help messages for each command
 */
void print_help_info()
{
    for(unsigned int a=0; a < ASCII_LINES; a++)
        std::cout << ascii_art[a] << std::endl;

    std::cout << std::endl << "Usage: mandelbrot [OPTION]..." << std::endl;
    for(unsigned int c=0; c < NUM_COMMANDS-1; c++)
    {
        std::cout << "  --" << long_opts[c].name << "  " << option_help[c] << std::endl;
    }
}

/*
 *
 */
static const char* short_opts = "s:x:y:o:c:z:vhr";

/*
 * get the program render settings from getopt_long
 * and parse it all into a reso_t struct
 */
Settings* get_render_settings(int argc, char** argv)
{
    // values used during the getopts phase
    int c;
    int found        = 0;
    int option_index = 0;

    // values to use in the struct (adjusted by the getopts args)
    uint8_t verbose       =            0;
    uint8_t random        =            0;
    double  init_real     =   DEFAULT_RE;
    double  init_imag     =   DEFAULT_IM;
    double  magnification = DEFAULT_ZOOM; // 0.5 will double the unit rect range

    //char*  fname; //strmcpy to this address from the getopt loop
    reso_t*     selected_reso = &all_resolutions[0];
    colormap_t* selected_map  = &all_colormaps[0];

    // begin getopts parsing
    while ((c = getopt_long(argc, argv, short_opts, long_opts, &option_index)) != -1)
        switch(c)
        {
            case 'v': // set the verbosity
                verbose = 1;
                break;

            case 'h': // print help and quit
                print_help_info();
                exit(0);      // exit here because we can't return-exit
                break;

            case 'r': // enable random point/zoom (overrides given coords)
                random = 1;
                break;

            case 's': // set the resolution target
                if(strlen(optarg) == 0)
                {
                    std::cerr << "No size given" << std::endl;
                    exit(1);
                }
                found = 0;
                for(uint32_t ri=0; ri < RESOLUTION_COUNT; ri++)
                {
                    if(strcmp(all_resolutions[ri].name, optarg) == 0)
                    {
                        selected_reso = &all_resolutions[ri];
                        found = 1;
                    }
                }
                if(!found)
                {
                    std::cerr << "Error: given resolution not supported" << std::endl;
                    print_supported_resolutions();
                    exit(1);
                }
                break;

            case 'c': // get the color
                if(strlen(optarg) == 0)
                {
                    std::cerr << "No color given" << std::endl;
                    exit(1);
                }
                found = 0;
                for(uint32_t ci=0; ci < COLORMAP_COUNT; ci++)
                {
                    if(strcmp(all_colormaps[ci].name, optarg) == 0)
                    {
                        selected_map = &all_colormaps[ci];
                        found = 1;
                    }
                }
                if(!found)
                {
                    std::cerr << "Error: given color scheme not supported" << std::endl;
                    exit(1);
                }
                break;

            case 'x': // get the real value
                if(strlen(optarg) == 0)
                {
                    std::cerr << "Error: no real number supplied" << std::endl;
                    exit(1);
                }
                init_real = atof(optarg); // can't errcheck because we accept sub-zero nums
                break;

            case 'y': // get the imag value
                if(strlen(optarg) == 0)
                {
                    std::cerr << "Error: no imaginary number supplied" << std::endl;
                    exit(1);
                }
                init_imag = atof(optarg);
                break;

            case 'z': // get the zoom value
                if(strlen(optarg) == 0)
                {
                    std::cerr << "Error: no zoom value given" << std::endl;
                    exit(1);
                }
                magnification = atof(optarg);
                if(magnification <= 0.0)
                {
                    std::cerr << "Error: negative or invalid zoom given" << std::endl;
                    exit(1);
                }
                break;
              
            case 'o': // get the file name to use
                if(strlen(optarg) == 0)
                {
                    std::cerr << "Error: no file path supplied" << std::endl;
                    exit(1);
                }
                // implement code to transfer char* to a std::string type
                // store the std::string type in the Settings for later usage
                break;
        }

    // Return the pointer to the new object allocated by RAII
    return new Settings(
            verbose,
            random,
            init_real,
            init_imag,
            magnification,
            selected_reso,
            selected_map
    );
}

#endif
