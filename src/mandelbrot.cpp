#include <iostream>
#include <fstream>
#include <getopt.h>

// use GMP soon for ultra precision
//#include <gmp.h>

// project level includes
#include "include/utils.h"

#define MAX_ITERS   255
#define THRESHOLD   4.0

/*
 * render a mandelbrot set based on the Settings* passed in
 */
int render(Settings* settings)
{
    // just print out some info dawg
    settings->display_info();

    // store local variables to avoid constant pointer accesses
    double w       = settings->res->width;
    double h       = settings->res->height;
    Gradient* grad = settings->grad;

    // open up a file stream and allocate the file header
    std::ofstream ofs("./mandel.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n";
    ofs << "#This is a mandelbrot image\n";
    ofs << w << " " << h;
    ofs << "\n255\n";

    // z values to mutate for iteration
    double z_re, z_re2;
    double z_im, z_im2;

    double init_re = settings->topleft_x; 
    double init_im = settings->topleft_y;
    double inc_re  = settings->inc_re;
    double inc_im  = settings->inc_im;

    double c_re = init_re; 
    double c_im = init_im;

    uchar iter;
    float iter_n;
    for(uint32_t y=0; y < h; y++)
    {
        for(uint32_t x=0; x < w; x++)
        {
            iter  = 0;
            z_re  = 0;
            z_im  = 0;
            z_re2 = 0;
            z_im2 = 0;

            while(z_re2 + z_im2 < THRESHOLD && iter++ < MAX_ITERS)
            {
                z_re2 = z_re * z_re;
                z_im2 = z_im * z_im;
                z_im  = (2.0 * z_re * z_im) + c_im;
                z_re  = z_re2 - z_im2 + c_re;
            }

            c_re += inc_re;
            ofs << iter << iter << iter;
        }
        c_re = init_re;
        c_im += inc_im;
    }

    ofs.close();
    if(settings->verbose)
        std::cout << "Finished writing image" << std::endl;
    return 0;
}

/* experimental method from wikipedia
int render2(Settings* s)
{
    // store local variables to avoid constant pointer accesses
    double w       = settings->res->width;
    double h       = settings->res->height;
    Gradient* grad = settings->grad;
    
    // z values to mutate for iteration
    double z_re, z_re2;
    double z_im, z_im2;

    double init_re = settings->topleft_x; 
    double init_im = settings->topleft_y;
    double inc_re  = settings->inc_re;
    double inc_im  = settings->inc_im;
    double c_re = init_re;

    // bailout radius
    double B = 256.0;
    double B2 = B*B;


    std::ofstream ofs("./output.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n";
    ofs << "#This is a mandelbrot image\n";
    ofs << w << " " << h;
    ofs << "\n255\n";

    uchar iter;
    for(uint32_t y=0; y < h; y++)
    {
        for(uint32_t x=0; x < w; x++)
        {


            while(z_re2 + z_im2 < 

        }
    }

    ofs.close();
    if(settings->verbose)
        std::cout << "Finished writing image" << std::endl;
    return 0;
}
*/

/*
 * The main function of the program
 */
int main(int argc, char **argv)
{
    Settings* render_settings;
    render_settings = get_render_settings(argc, argv);

    render(render_settings);

    return 0;
}
