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
#include "include/functions.h"

// constants to use
// Julia has a higher breakout range than Mandel
#define MAX_ITERS  255.0
#define M_BREAKOUT 4.0
#define J_BREAKOUT 100.0
#define LOG2       0.6931471805599453


namespace render
{
    /*
     * Create an ofstream image object and return the pointer
     * for us to use in the rendering programs
     */
    std::ofstream* create_image(std::string name, opts::Settings& s)
    {
        std::ofstream* ofs;
        ofs = new std::ofstream(name, std::ios::out | std::ios::binary);
        *ofs << "P6\n";
        *ofs << "#Real: " << s.topleft_x << ", Imag: " << s.topleft_y << "\n";
        *ofs << s.res->width << " " << s.res->height;
        *ofs << "\n255\n";
        return ofs;
    }


    /*
     * Iterate a given point z with constant C
     * to create the Mandelbrot set (z^2 + c)
     */
    double iterate_m(Cmp& z, const Cmp& c)
    {
        double count = 0.0;
#ifdef DGMP
#else
        while(z.length2() < M_BREAKOUT && count++ < MAX_ITERS)
        {
            z.mul(z);
            z.add(c);
        }
#endif

        return count;
    }


    /*
     * Iterate a given z-point with constant C
     * and an assigned Julia set function
     */
    double iterate_j(Cmp& z, const Cmp& c, const funcs::JFunc_t& jf)
    {
        double count = 0.0;

#ifdef DGMP
#else
        while(z.length2() < J_BREAKOUT && count++ < MAX_ITERS)
        {
            jf(z, c);
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
        std::ofstream* ofs = create_image("./mandelbrot.ppm", s);

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
                c.add(xbump);
            }
            c.real = init_re;
            c.add(ybump);
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
        uint32_t w     = s.res->width;
        uint32_t h     = s.res->height;

        double init_re = s.topleft_x;
        double init_im = s.topleft_y;
        double inc_re  = s.inc_re;
        double inc_im  = s.inc_im;

        // example constants to use for C
        double c_re    = -0.8;
        double c_im    = 0.156;
        
        Cmp       z(0, 0);
        const Cmp c(c_re, c_im);
        Cmp       pos(init_re, init_im);
        Cmp       xbump(inc_re, 0), ybump(0, inc_im);

        std::ofstream* ofs = create_image("./julia.ppm", s);

        // pick a function from the pre-defined func pointers
        const funcs::JuliaFunc* picked = &funcs::all[0];

        double i = 0.0;
        uint8_t result = 0;

        for(uint32_t y=0; y < h; y++)
        {
            for(uint32_t x=0; x < w; x++)
            {
                z.real = pos.real;
                z.imag = pos.imag;

                i = iterate_j(z, c, picked->func);

                result = colors::flatten(i);
                *ofs << result << result << result;
                pos.add(xbump);
            }
            pos.real = init_re;
            pos.add(ybump);
        }

        ofs->close();
        return 0;
    }
}

// end
