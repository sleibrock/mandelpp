/*
 * rendering.cpp
 *
 * All code for rendering Mandelbrot images
 * should be linked from main programs
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

#include "include/rendering.h"
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
            // avoid object creation by using arith-assign
            z *= z;
            z += c;
        }
#endif

        return count;
    }

    double iterate_j(Cmp& z, const Cmp& c, const JFunc& jf)
    {
        double count = 0.0;

#ifdef DGMP
#else
        while(z.length2() < THRESHOLD && count++ < MAX_ITERS)
        {
            z = jf(z, c);
        }
        
#endif

        return count;
    }


    /*
     * Main mandelbrot rendering function
     * Accepts a Settings ref and renders
     * the Mandelbrot set of f(z) = z^2 + c
     */
    int mandelbrot(opts::Settings& s)
    {
        s.display_info();

        uint32_t w = s.res->width;
        uint32_t h = s.res->height;
        double init_re = s.topleft_x;
        double init_im = s.topleft_y;
        double inc_re  = s.inc_re;
        double inc_im  = s.inc_im;
        Cmp z(0, 0), c(init_re, init_im);
        Cmp xbump(inc_re, 0), ybump(0, inc_im);
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


    /*
     * Main Julia function
     * Executes a given Julia function (anything)
     * and renders the set
     */
    int julia(opts::Settings& s)
    {
        s.display_info();
        uint32_t w = s.res->width;
        uint32_t h = s.res->height;

        double init_re = s.topleft_x;
        double init_im = s.topleft_y;
        double inc_re = s.inc_re;
        double inc_im = s.inc_im;
        Cmp z(0, 0), c(init_re, init_im);
        Cmp xbump(inc_re, 0), ybump(0, inc_im);

        std::ofstream* ofs = create_image("./julia.ppm", w, h);

        // create a vector of functions
        std::vector<JFunc> v;
        v.push_back([](Cmp z, Cmp c){ return (z*z) + c; });
        JFunc picked = v[0];

        double i, result;

        for(uint32_t y=0; y < h; y++)
        {
            for(uint32_t x=0; x < w; x++)
            {
                z.real = 0.0;
                z.imag = 0.0;

                i = iterate_j(z, c, picked);

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

}

// end
