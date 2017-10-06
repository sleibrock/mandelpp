#include <iostream>
#include "include/opts.h"
#include "include/resolutions.h"
#include "include/colors.h"

namespace opts
{
    // adjust these when you add more commands
    const uint32_t  M_COMMANDS = 10;
    const uint32_t  J_COMMANDS = 11;
    const uint32_t ASCII_LINES = 9;


    // Mandelbrot ascii art for -h(elp)
    const char* mandel_art[] =
    {
        "-------------------------",
        "|              ..***.   |",
        "|       .    .*******.  |",
        "|   .  .*.  .********.  |",
        "|  .*..***..********.   |",
        "|   .  .*.  .********.  |",
        "|       .    .*******.  |",
        "|              ..***.   |",
        "-------------------------",
    };


    // Julia ascii art for -h(elp)
    const char* julia_art[] =
    {
        "-------------------------",
        "|                       |",
        "|                       |",
        "|                       |",
        "|                       |",
        "|                       |",
        "|                       |",
        "|                       |",
        "-------------------------",
    };


    /*
    * getopt_long arguments
    * 0 - no_arg, 1 - mandatory, 2 - arg required
    */
    const struct option mlong_opts[] =
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
    const char* mshort_opts = "s:x:y:o:c:z:vhr";
    const char* moption_help[] =
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


    const struct option jlong_opts[] =
    {
        {"size",     2,    0, 's'},
        {"real",     2,    0, 'x'},
        {"imag",     2,    0, 'y'},
        {"output",   2,    0, 'o'},
        {"colors",   2,    0, 'c'},
        {"function", 2,    0, 'f'},
        {"zoom",     2,    0, 'z'},
        {"random",   0,    0, 'r'},
        {"verbose",  0,    0, 'v'},
        {"help",     0,    0, 'h'},
        {NULL,       0, NULL,   0}
    };


    const char* jshort_opts = "s:x:y:o:c:f:z:vhr";
    const char* joption_help[] =
    {
        "sets the target resolution of the output image",
        "sets the initial Constant real value to use",
        "sets the initial Constant imaginary value to use",
        "tells the program what name to use for the output file",
        "informs the program what color map to use",
        "sets the Julia function to render",
        "sets the zoom/magnification level",
        "selects a random Constant variable to use",
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


    /*
     * Print out the Mandelbrot program commands
     */
    void print_mandel_info()
    {
        for(uint32_t a=0; a < ASCII_LINES; a++)
            std::cout << mandel_art[a] << std::endl;


        std::cout << std::endl << "Usage: mandelbrot [OPTION]..." << std::endl;
        for(uint32_t h=0; h < M_COMMANDS-1; h++)
            std::cout << "  --" << mlong_opts[h].name << ", " << moption_help[h] << std::endl;
    }


    /*
     * Print out the Julia program commands
     */
    void print_julia_info()
    {
        for(uint32_t a=0; a < ASCII_LINES; a++)
            std::cout << julia_art[a] << std::endl;

        std::cout << std::endl << "Usage: julia [OPTION]..." << std::endl;
        for(uint32_t h=0; h < J_COMMANDS-1; h++)
            std::cout << "  --" << jlong_opts[h].name << ", " << joption_help[h] << std::endl;
    }


    /*
     * Arg-parsing utility for the Mandelbrot program
     * Specific to Mandelbrot because of the differences
     * Between the two programs
     */
    Settings mparse(int argc, char** argv)
    {
        // values used during the getopts phase
        int c            = 0;
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
        while ((c = getopt_long(argc, argv, mshort_opts, mlong_opts, &option_index)) != -1)
            switch(c)
            {
            case 'v':
                // verbosity switch
                verbose = 1;
                break;

            case 'h':
                // print help and quit
                print_mandel_info();
                exit(0);
                break;

            case 'r':
                // enable random mode
                random = 1;
                break;

            case 's':
                // set the resolution rect from ones available
                if(strlen(optarg) == 0)
                {
                    std::cerr << "No size given" << std::endl;
                    exit(1);
                }

                // linear search to find the supplied reso
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

            case 'x':
                // take the supplied real value
                if(strlen(optarg) == 0)
                {
                    std::cerr << "Error: no real number supplied" << std::endl;
                    exit(1);
                }

                // set the real (no checking, bad)
                init_real = atof(optarg);
                break;

            case 'y':
                // get the supplied imag value
                if(strlen(optarg) == 0)
                {
                    std::cerr << "Error: no imaginary number supplied" << std::endl;
                    exit(1);
                }

                // set the imag num (no checking, bad)
                init_imag = atof(optarg);
                break;

            case 'z':
                // get the zoom value
                if(strlen(optarg) == 0)
                {
                    std::cerr << "Error: no zoom value given" << std::endl;
                    exit(1);
                }

                // magnification can be checked as to prevent zeroes
                magnification = atof(optarg);
                if(magnification <= 0.0)
                {
                    std::cerr << "Error: negative or invalid zoom given" << std::endl;
                    exit(1);
                }
                break;

            case 'o':
                // get the file name and bind it
                if(!strlen(optarg))
                {
                    std::cerr << "Error: no file path supplied" << std::endl;
                    exit(1);
                }

                // TODO: transfer char* to a std::string type
                break;
            }

        // Return a new Settings object by value
        return Settings
            (
                verbose, random, init_real,
                init_imag, magnification, &reso::all[selected_reso]
            );
    }


    /*
     * Julia-specific version of mparse (similar code, different opts)
     */
    Settings jparse(int argc, char** argv)
    {

        // values used during the getopts phase
        int      c             =            0;
        int      found         =            0;
        int      option_index  =            0;
        // values to use in the struct (adjusted by the getopts args)
        uint8_t  verbose       =            0;
        uint8_t  random        =            0;
        double   init_real     =   DEFAULT_RE;
        double   init_imag     =   DEFAULT_IM;
        double   magnification = DEFAULT_ZOOM; // 0.5 will double the unit rect range

        //char*  fname; //strmcpy to this address from the getopt loop
        uint32_t selected_reso = 0;

        // begin getopts parsing
        while ((c = getopt_long(argc, argv, mshort_opts, mlong_opts, &option_index)) != -1)
            switch(c)
            {
            case 'v':
                // verbosity switch
                verbose = 1;
                break;

            case 'h':
                // print help and quit
                print_julia_info();
                exit(0);
                break;

            case 'r':
                // enable random mode
                random = 1;
                break;

            case 's':
                // set the resolution rect from ones available
                if(strlen(optarg) == 0)
                {
                    std::cerr << "No size given" << std::endl;
                    exit(1);
                }

                // linear search to find the supplied reso
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

            case 'x':
                // take the supplied real value
                if(strlen(optarg) == 0)
                {
                    std::cerr << "Error: no real number supplied" << std::endl;
                    exit(1);
                }

                // set the real (no checking, bad)
                init_real = atof(optarg);
                break;

            case 'y':
                // get the supplied imag value
                if(strlen(optarg) == 0)
                {
                    std::cerr << "Error: no imaginary number supplied" << std::endl;
                    exit(1);
                }

                // set the imag num (no checking, bad)
                init_imag = atof(optarg);
                break;

            case 'z':
                // get the zoom value
                if(strlen(optarg) == 0)
                {
                    std::cerr << "Error: no zoom value given" << std::endl;
                    exit(1);
                }

                
                // magnification can be checked as to prevent zeroes
                magnification = atof(optarg);
                if(magnification <= 0.0)
                {
                    std::cerr << "Error: negative or invalid zoom given" << std::endl;
                    exit(1);
                }
                break;

            case 'o':
                // get the file name and bind it
                if(strlen(optarg) == 0)
                {
                    std::cerr << "Error: no file path supplied" << std::endl;
                    exit(1);
                }

                // TODO: transfer char* to a std::string type
                break;
            }

        // Return a new Settings object by value
        return Settings
            (
                verbose, random, init_real,
                init_imag, magnification, &reso::all[selected_reso]
            );
    }
}

// end
