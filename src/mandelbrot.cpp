#include <iostream>
#include <fstream>

#include "include/complex.h"
#include "include/opts.h"


// use GMP soon for ultra precision
//#include <gmp.h>

#define MAX_ITERS   255.0
#define THRESHOLD   4.0
#define LOG2        0.6931471805599453


/*
 * Take in a Complex value and iterate it
 * until it escapes the boundary threshold or exceeds
 * the maximum iteration (MAX_ITERS)
 * Calculating depends on whether libgmp is compiled
 */
double iterate(Cmp& z, const Cmp& c)
{
    double count = 0;

#ifdef DGMP
#else
    while(z.length2() < THRESHOLD && count++ < MAX_ITERS)
    {
        z = (z*z*z) + c;
        //std::cout << "Current z is " << z << std::endl;
    }
#endif

    return count;
}


/*
 * Main rendering function to render data to an image
 */
int render_image(opts::Settings& s)
{
    // store local vars
    double    w    = s.res->width;
    double    h    = s.res->height;

    s.display_info();

    double init_re = s.topleft_x;
    double init_im = s.topleft_y;
    double inc_re  = s.inc_re;
    double inc_im  = s.inc_im;

    // iteration values
    Cmp z(0, 0), c(init_re, init_im);
    Cmp xbump(inc_re, 0);
    Cmp ybump(0, inc_im);

    std::ofstream ofs("./output.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n";
    ofs << "#This is a mandelbrot image\n";
    ofs << w << " " << h;
    ofs << "\n255\n";

    double i = 0;
    uint8_t result = 0;

    double init_zx, init_zy;
    init_zx = -0.8;
    init_zy = 0.156;

    for(uint32_t y=0; y < h; y++)
    {
        for(uint32_t x=0; x < w; x++)
        {
            z.real = init_zx;
            z.imag = init_zy;

            i = iterate(z, c);

            result = colors::flatten(i);
            ofs << result << result << result;
            c += xbump;
        }
        c.real = init_re;
        c += ybump;
    }

    ofs.close();

    return 0;
}

// end
