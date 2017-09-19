#include <iostream>
#include <fstream>

#include "include/complex.h"
#include "include/rendering.h"
#include "include/opts.h"


// use GMP soon for ultra precision
//#include <gmp.h>

#define MAX_ITERS   255.0
#define THRESHOLD   4.0
#define LOG2        0.6931471805599453


/*
 * Main Mandelbrot rendering program
 */
int main(int argc, char **argv)
{
    srand(time(0));
    opts::Settings rs = opts::mparse(argc, argv);

    render::mandelbrot(rs);

    return 0;
}

// end
