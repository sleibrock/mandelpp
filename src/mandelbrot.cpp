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
    
    
    if(settings->verbose)
    {
        std::cout << "===================================" << std::endl;
        std::cout << "|       Mandelbrot Program        |" << std::endl;
        std::cout << "===================================" << std::endl;
        std::cout << std::endl;

        std::cout << "Target resolution: " << settings->output_res->width 
            << "x" << settings->output_res->height << std::endl;
        std::cout << std::endl;

        //std::cout << "Desired point: " << init_re << ", " << init_im << std::endl;
        //std::cout << "Magnification: " << magnification << std::endl;
        //std::cout << "Top-left point: " << top_x << ", " << top_y << std::endl;
        std::cout << "Increment: " << inc << std::endl;

        std::cout << std::endl;
        std::cout << "Beginning iteration ... " << std::endl;
    }

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
    std::cout << "Breaking program" << std::endl;
    Settings* render_settings;
    render_settings = get_render_settings(argc, argv);
    std::cout << "Passing to render stage" << std::endl;

    render(render_settings);

    // exit
    return 0;
}
