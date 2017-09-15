#ifndef _RENDERING_H
#define _RENDERING_H

#include <iostream>
#include <fstream>

#include "complex.h"
#include "opts.h"

namespace render
{
    std::ofstream* create_image(std::string, uint32_t, uint32_t);
    double iterate_m(Cmp&, const Cmp&);
    double iterate_j(Cmp&, const Cmp&);
    int mandelbrot(opts::Settings&);
    int julia(opts::Settings&);
}

#endif
