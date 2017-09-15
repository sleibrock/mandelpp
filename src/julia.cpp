#include <iostream>
#include <fstream>

/*
 * julia.cpp
 *
 * The main Julia set generating program
 */

#include "include/complex.h"
#include "include/opts.h"
#include "include/rendering.h"

/*
 * Main Julia rendering program
 */
int main(int argc, char** argv)
{
    srand(time(0));
    opts::Settings rs = opts::jparse(argc, argv);

    render::julia(rs);
    
    return 0;
}
