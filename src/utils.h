/*
 * This file is used to define generic utilities for the project
 *
 * Contains: 
 *   program version constant
 *   program options and their help messages
 *   render settings struct and other stuffs surrounding it
 *   ascii art!
 */

#ifndef _MANDEL_UTILS_H
#define _MANDEL_UTILS_H

#include <iostream>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <string.h>

#define PROGRAM_VERSION        0.1
#define NUM_COMMANDS            10
#define RESOLUTION_COUNT        13
#define ASCII_LINES              9
#define DEFAULT_ZOOM           0.5
#define DEFAULT_RE            -0.7
#define DEFAULT_IM             0.0


//////////////////////////////////////////////////////// BEGIN CLASS/STRUCT/ARR DEFS
// the resolution struct that contains output size info
typedef struct reso_t {
    const char*  name;
    const unsigned int width;
    const unsigned int height;
} reso_t;

static reso_t all_resolutions[RESOLUTION_COUNT] = {
    // standard resolution outputs
    {"480p",       640,    480},
    {"720p",      1280,    720},
    {"768p",      1024,    768},
    {"900p",      1600,    900},
    {"1080p",     1920,   1080},
    {"1440p",     2560,   1440},

    // highly deadly resolutions
    {"4k",        3840,   2160},
    {"8k",        7680,   4320},
    {"16k",      15360,   8640},  // ~400mb
    {"32k",      30720,  17280},  // ~1.6gb !!!!
    {"64k",      61440,  34560},  // ~6gb, god help us all

    // unconventional rendering resolutions 
    {"twitter",   1024,    576},
    {"instagram", 1024,    768},

};

static const char* ascii_art[ASCII_LINES] = {
    "------------------*------",
    "---------------******----",
    "--------*-----********---",
    "----*--***--**********---",
    "--*******************----",
    "----*--***--**********---",
    "--------*----*********---",
    "--------------*******----",
    "------------------*------",
};

// getopt_long arguments
// 0 - no_arg, 1 - mandatory, 2 - arg required
static struct option long_options[NUM_COMMANDS] = {
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

static const char* option_help[NUM_COMMANDS] = {
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

class Settings
{
public:
    unsigned char verbose;
    unsigned char color_map;
    unsigned char random;
    double init_real;
    double init_imag;
    double zoom;
    // char* fname;
    reso_t*  res;

    double span_x;
    double span_y;
    double topleft_x;
    double topleft_y;
    double botright_x;
    double botright_y;

    double inc_re;
    double inc_im;

    // constructor - do all the dimensional alignment/math here
    Settings(unsigned char  v, unsigned char  r, 
             unsigned char cm, double        ir,
             double        ii, double         z,
             reso_t* out)
    {
        verbose   =   v;
        color_map =  cm;
        random    =   r;
        init_real =  ir;
        init_imag =  ii;
        zoom      =   z;
        res       = out;

        double w = double(res->width);
        double h = double(res->height);
        span_x = ((w/h) * 0.5) * (1.0 / zoom);
        span_y = 0.5           * (1.0 / zoom);

        topleft_x  = init_real - span_x;
        topleft_y  = init_imag - span_y;
        botright_x = init_real + span_x;
        botright_y = init_imag + span_y;

        inc_re = (fabs(topleft_x - botright_x)) * (1.0 / w);
        inc_im = (fabs(topleft_y - botright_y)) * (1.0 / h);
    }

    void display_info()
    {
        if(!verbose)
            return;

        // print some basic stuff
        if(random)
        {
            std::cout << "Random mode enabled!";
        }

        std::cout << "Target resolution: " << res->width << "x"  << res->height << std::endl;
        std::cout << "Desired point: "     <<  init_real << ", " <<   init_imag << std::endl;
        std::cout << "Spans: "             <<     span_x << ", " <<      span_y << std::endl;
        std::cout << "Top left: "          <<  topleft_x << ", " <<   topleft_y << std::endl;
        std::cout << "Bot right: "         << botright_x << ", " <<  botright_y << std::endl;
        std::cout << "Increments: "        <<     inc_re << ", " <<      inc_im << std::endl;
        std::cout << "Magnification: "     <<       zoom <<                        std::endl;

    };
};
//////////////////////////////////////////////////////// END S/C/A DEFS

/////////////////////////////////////////////////////// BEGIN HELP INFO SECTION
void print_supported_resolutions()
{
    std::cout << "Supported resolutions list: " << std::endl << std::endl;
    std::cout << "idk" << std::endl;
};

void print_help_info()
{
    for(unsigned int a=0; a < ASCII_LINES; a++)
        std::cout << ascii_art[a] << std::endl;

    std::cout << std::endl << "Commands: " << std::endl;
    for(unsigned int c=0; c < NUM_COMMANDS-1; c++)
    {
        std::cout << "  --" << long_options[c].name << "  " << option_help[c] << std::endl; 
    }
}

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
    unsigned int verbose      =    0;
    unsigned int color        =    0;
    unsigned int random       =    0;
    double magnification      = DEFAULT_ZOOM; // 0.5 will double the unit rect range
    double init_real          = DEFAULT_RE;
    double init_imag          = DEFAULT_IM;
    //char*  fname; //strmcpy to this address from the getopt loop
    reso_t* selected_reso     = &all_resolutions[0];

    // begin getopts parsing
    while ((c = getopt_long(argc, argv, "s:x:y:o:c:z:vhr",
                            long_options, &option_index)) != -1)
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
                for(unsigned int ri=0; ri < RESOLUTION_COUNT; ri++)
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
                break;
            
        }

    return new Settings(
            verbose,
            color,
            random,
            init_real,
            init_imag,
            magnification,
            selected_reso
    );
    // done handling getopts
}

/////////////////////////////////////////////////////////// END RENDER INFO SECTION
#endif
