#include <iostream>
#include <fstream>
#include <getopt.h>

// use GMP soon for ultra precision
//#include <gmp.h>

// project level includes
#include "include/utils.h"

#define MAX_ITERS   255
#define THRESHOLD   4.0
#define LOG2        0.6931471805599453

int render2(Settings* s)
{
    // store local variables to avoid constant pointer accesses
    double w       = s->res->width;
    double h       = s->res->height;
    Gradient* grad = s->grad;
    
    // z values to mutate for iteration
    double z_re, z_re2;
    double z_im, z_im2;

    double init_re = s->topleft_x; 
    double init_im = s->topleft_y;
    double inc_re  = s->inc_re;
    double inc_im  = s->inc_im;
    double c_re = init_re;
    double c_im = init_im;

    // bailout radius
    const double B = 256.0;
    const double B2 = B*B;

    s->display_info();
    color_t color = {0.0, 0.0, 0.0};

    std::ofstream ofs("./output.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n";
    ofs << "#This is a mandelbrot image\n";
    ofs << w << " " << h;
    ofs << "\n255\n";

    // additional stuff
    double log_zn = 0.0;
    double nu = 0.0;

    uchar  iter;
    double iterf;
    double perc;   // used to calculate interpolation
    for(uint32_t y=0; y < h; y++)
    {
        for(uint32_t x=0; x < w; x++)
        {

            iter  = 0;
            iterf = 0;
            z_re  = 0;
            z_im  = 0;
            z_re2 = 0;
            z_im2 = 0;

            while(z_re2 + z_im2 < B2 && iter < MAX_ITERS)
            {
                z_re2 = z_re * z_re;
                z_im2 = z_im * z_im;
                z_im  = (2.0 * z_re * z_im) + c_im;
                z_re  = z_re2 - z_im2 + c_re; 
                iter++;
                iterf += 1.0;
            }

            // estimate how far we were from diverging and create a smoothed color
            if(iter< MAX_ITERS)
            {
                log_zn = log(z_re2 + z_im2) * 0.5;
                nu     = log( log_zn / LOG2 ) / LOG2;
                iter   = iter + 1.0 - nu;
                perc = iterf - floor(iterf);
                grad->interp(floor(iterf), (double)MAX_ITERS, perc, &color);
            }
            else 
            {
                // we hit the max iter so max values should be colored black
                grad->reset(&color);
            }

            // write the current color to file
            ofs << flatten(color.r) << flatten(color.g) << flatten(color.b);
            
            // increment x to proceed to next pixel
            c_re += inc_re;
        }
        c_re = init_re;
        c_im += inc_im;
    }

    ofs.close();
    if(s->verbose)
        std::cout << "Finished writing image" << std::endl;
    return 0;
}

/*
 * The main function of the program
 */
int main(int argc, char **argv)
{
    Settings* render_settings;
    render_settings = get_render_settings(argc, argv);

    render2(render_settings);

    return 0;
}
