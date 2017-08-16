#include <iostream>
#include <fstream>
#include <cstdint>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <math.h>

// use GMP soon for ultra precision
//#include <gmp.h>

// project level includes
#include "utils.h"

#define MAX_ITERS              255

/*
 * render a mandelbrot set based on the settings_t var
 */
int render(Settings* settings)
{
    settings->display_info();

    // open up a file stream and allocate the file header
    std::ofstream ofs("./mandel.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n";
    ofs << "#This is a mandelbrot image\n";
    ofs << settings->output_res->width << " " << settings->output_res->height;
    ofs << "\n255\n";

    double inc  = 0.01;
    // constant C values
    double c_re = settings->init_real;
    double c_im = settings->init_imag;

    // z values to mutate for iteration
    double z_re, z_re2;
    double z_im, z_im2;

    // width-to-height ratio
    // the x will always be more than the y
    // so for a widescreen, the render box should be (0,0) to (ratio, 1)
    double ratio = settings->output_res->width / settings->output_res->height;
    
    unsigned char iter;
    for(unsigned int y=0; y < settings->output_res->height; y++)
    {
        for(unsigned int x=0; x < settings->output_res->width; x++)
        {
            iter = 0;

            while(0){
                // mutate
            }
            c_re += inc;
            ofs << iter << iter << iter;
        }
        c_re = settings->init_real;
        c_im += inc;
    }

    ofs.close();
    if(settings->verbose)
        std::cout << "Finished writing image" << std::endl;
    return 0;
}


int main(int argc, char **argv)
{
    Settings* render_settings;
    render_settings = get_render_settings(argc, argv);
    render(render_settings);
    return 0;
}
