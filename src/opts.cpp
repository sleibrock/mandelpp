#include <iostream>
#include "include/opts.h"
#include "include/resolutions.h"
#include "include/colors.h"

namespace opts
{
    /*
     * Ascii art to decorate the -h(elp) message
     */
    const char* ascii_art[ASCII_LINES] =
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
    const struct option long_opts[NUM_COMMANDS] =
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
    const char* short_opts = "s:x:y:o:c:z:vhr";
    const char* option_help[NUM_COMMANDS] =
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
    
    
    Settings::Settings(uint8_t v, uint8_t r, double ir, double ii, double z, const reso::rect_t* out)
    {
        verbose = v;
        random  = r;
        
        // add a random mode here somewhere
        if(!random)
        {
            init_real = ir;
            init_imag = ii;
            zoom      = z;
        }
        else
        {
            //disabled for now
            init_real = 0;
            init_imag = 0;
            zoom      = 1;
            
        }
        
        res = out;
        
        double w   = double(res->width);
        double h   = double(res->height);
        
        span_x     = ((w/h) * 0.5) * (1.0 / zoom);
        span_y     =          0.5  * (1.0 / zoom);
        
        topleft_x  = init_real - span_x;
        topleft_y  = init_imag - span_y;
        
        botright_x = init_real + span_x;
        botright_y = init_imag + span_y;
        
        inc_re     = (fabs(topleft_x - botright_x)) * (1.0 / w);
        inc_im     = (fabs(topleft_y - botright_y)) * (1.0 / h);
        
    }
    
    void Settings::display_info()
    {
        if(!verbose)
            return;
        
        // print some basic stuff
        if(random)
            std::cout << "*** Random mode enabled! ***" << std::endl;
        
        std::cout << "Target resolution: " << res->width << "x" << res->height << std::endl;
        std::cout << "Desired point:     " <<  init_real << "x" <<   init_imag << std::endl;
        std::cout << "Spans:             " <<     span_x << "x" <<      span_y << std::endl;
        std::cout << "Top left:          " <<  topleft_x << "x" <<   topleft_y << std::endl;
        std::cout << "Bot right:         " << botright_x << "x" <<  botright_y << std::endl;
        std::cout << "Increments:        " <<     inc_re << "x" <<      inc_im << std::endl;
        std::cout << "Magnification:     " <<       zoom <<                       std::endl;
    }
    
    void print_help_info()
    {
        for(uint32_t a=0; a < ASCII_LINES; a++)
            std::cout << ascii_art[a] << std::endl;

        std::cout << std::endl << "Usage: mandelbrot [OPTION]..." << std::endl;
        for(uint32_t h=0; h < NUM_COMMANDS-1; h++)
            std::cout << "  --" << long_opts[h].name << " " << option_help[h] << std::endl;
    }
    
    
    Settings parse(int argc, char** argv)
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
        uint32_t selected_reso = 0;
        
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
                    if(strcmp(reso::all[ri].name, optarg) == 0)
                    {
                        selected_reso = ri;
                        found = 1;
                    }
                }
                if(!found)
                {
                    std::cerr << "Error: given resolution not supported" << std::endl;
                    reso::print_all();
                    exit(1);
                }
                break;
                
                /*
            case 'c': // get the color
                if(strlen(optarg) == 0)
                {
                    std::cerr << "No color given" << std::endl;
                    exit(1);
                }
                found = 0;
                for(uint32_t ci=0; ci < COLORMAP_COUNT; ci++)
                {
                    if(strcmp(colors::all_colormaps[ci].name, optarg) == 0)
                    {
                        selected_map = &colors::all_colormaps[ci];
                        found = 1;
                    }
                }
                if(!found)
                {
                    std::cerr << "Error: given color scheme not supported" << std::endl;
                    colors::print_color_info();
                    exit(1);
                }
                break;
                */
                
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
        return Settings(
            verbose,
            random,
            init_real,
            init_imag,
            magnification,
            &reso::all[selected_reso]
            );
    }
    
}
