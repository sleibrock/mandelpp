#include <iostream>
#include <fstream>
#include <cstdint>
#include <unistd.h>
#include <stdlib.h>

// use GMP soon for ultra precision
//#include <gmp.h>

#define MAX_ITERS              255
#define DEFAULT_WIDTH         7680
#define DEFAULT_HEIGHT        4320
#define MANDELBROT_THRESHOLD   4.0

/*
// program args with getopts/unistd
static struct option long_options[5] = {
    {"real",   1, 0,    0},
    {"imag",   1, 0,    0},
    {"output", 1, 0,    0},
    {"colors", 1, 0,    0},
    {NULL,     0, NULL, 0}
};
*/

int main(int argc, char **argv)
{
    // Command line options
    // --width=<uint32_t>  - width of the output image
    // --height=<uint32_t> - height of the output image
    // --real=<double>     - starting position (x, real)
    // --imag=<double>     - starting position (y, imag)
    // --output=<string>   - file output name (output.ppm)
    // --colors=<string>   - name of the color map to use
    // --verbose           - print info for debug purposes 

    // make that nice 8k res image
    uint32_t width  = DEFAULT_WIDTH;
    uint32_t height = DEFAULT_HEIGHT;

    // write data to a file
    std::ofstream ofs("./mandel.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n";
    ofs << "#This is a mandelbrot image\n";
    ofs << width << " " << height << "\n255\n";

    // use to print out more text
    int verbose = 1;

    // magnification level - increase to zoom in more, decrease for less (!=0)
    const double magnification = 64000;

    // seeds - the center of the image is (init_re, init_im)
    const double init_re = -0.1011;
    const double init_im = 0.9563;
    const double inc_re  = (1.0 / magnification);
    const double inc_im  = (1.0 / magnification);

    // find the top-left x-y pair
    const double top_x  = init_re - ((double(width)*0.5) * inc_re);
    const double top_y = init_im - ((double(height)*0.5) * inc_im);

    // constant C values
    double c_re = top_x;
    double c_im = top_y;

    // z values to mutate for iteration
    double z_re, z_re2;
    double z_im, z_im2;

    if(verbose)
    {
        std::cout << "===================================" << std::endl;
        std::cout << "|       Mandelbrot Program        |" << std::endl;
        std::cout << "===================================" << std::endl;
        std::cout << std::endl;

        std::cout << "Desired point: " << init_re << ", " << init_im << std::endl;
        std::cout << "Magnification: " << magnification << std::endl;
        std::cout << "Top-left point: " << top_x << ", " << top_y << std::endl;
        std::cout << "Increments: " << inc_re << ", " << inc_im << std::endl;

        std::cout << std::endl;
        std::cout << "Beginning iteration ... " << std::endl;
    }

    // new increment-based method
    unsigned char iter;
    for(unsigned int y=0; y< height; y++)
    {
        for(unsigned int x=0; x < width; x++)
        {
            // reset the values for the x-loop
            iter  = 0;
            z_re  = 0.0;
            z_im  = 0.0;
            z_re2 = 0.0;
            z_im2 = 0.0;

            while((z_re2+z_im2 < MANDELBROT_THRESHOLD) && iter++ < MAX_ITERS)
            {
                z_re2 = z_re * z_re;
                z_im2 = z_im * z_im;
                z_im = (2.0 * z_re * z_im) + c_im;
                z_re = z_re2 - z_im2 + c_re;
            }
            c_re += inc_re;

            // write to file a triplet of colors (r,g,b)
            // apply color scheme indexing/histogramming here
            ofs << iter << iter << iter;
        }
        c_im += inc_im; // update the c_im component
        c_re = init_re; // reset the c_real component
    }

    if(verbose)
        std::cout << "Finished! Image stored in mandel.ppm" << std::endl;

    // close the file
    ofs.close();

    // exit
    return 0;
}
