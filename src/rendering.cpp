/*
 * rendering.cpp
 *
 * All code for rendering Mandelbrot images
 * should be linked from main programs
 */


#include <iostream>
#include <fstream>

#include "include/complex.h"
#include "include/opts.h"

#define MAX_ITERS 255.0
#define THRESHOLD 4.0
#define LOG2      0.6931471805599453


namespace render
{

    /*
     * Create an ofstream image object and return the pointer
     * for us to use in the rendering programs
     */
    std::ofstream* create_image(std::string name, uint32_t w, uint32_t h)
    {
        std::ofstream* ofs;
        ofs = new std::ofstream(name, std::ios::out | std::ios::binary);

        *ofs << "P6\n";
        *ofs << "#This is a comment\n";
        *ofs << w << " " << h;
        *ofs << "\n255\n";

        return ofs;
    }
    
    double iterate_m(Cmp& z, const Cmp& c)
    {
        double count = 0.0;
#ifdef DGMP
#else
        while(z.length2() < THRESHOLD && count++ < MAX_ITERS)
        {
            z = (z*z) + c;
        }
#endif

        return count;
    }

    double iterate_j(Cmp& z, const Cmp& c)
    {
        double count = 0.0;

#ifdef DGMP
#else
        while(z.length2() < THRESHOLD && count++ < MAX_ITERS)
        {
            z = (z*z*z) + c;
        }
        
#endif

        return count;
    }

    int mandelbrot(opts::Settings& s)
    {
        s.display_info();

        double w = s.res->width;
        double h = s.res->height;

        double init_re = s.topleft_x;
        double init_im = s.topleft_y;

        double inc_re = s.inc_re;
        double inc_im = s.inc_im;

        Cmp z(0, 0), c(init_re, init_im);
        Cmp xbump(inc_re, 0), ybump(0, inc_im);

        /*
    std::ofstream ofs("./output.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n";
    ofs << "#This is a Julia set image\n";
    ofs << w << " " << h;
    ofs << "\n255\n";
        */
        std::ofstream* ofs = create_image("./mandelbrot.ppm", w, h);

        double i = 0;
        uint8_t result = 0;

        for(uint32_t y=0; y < h; y++)
        {
            for(uint32_t x=0; x < w; x++)
            {
                z.real = 0.0;
                z.imag = 0.0;

                i = iterate_m(z, c);

                result = colors::flatten(i);
                *ofs << result << result << result;
                c += xbump;
            }
            c.real = init_re;
            c += ybump;
        }

        ofs->close();
        

        return 0;

    }

    int julia(opts::Settings& s)
    {
        return 0;

    }

}

// end
