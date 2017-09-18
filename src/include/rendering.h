#ifndef _RENDERING_H
#define _RENDERING_H

#include <iostream>
#include <fstream>
#include <functional>

#include "complex.h"
#include "opts.h"

namespace render
{
    // A julia function represented as a Lambda type
    typedef std::function<Cmp(Cmp&, const Cmp&)> JFunc;

    
    std::ofstream* create_image(std::string, uint32_t, uint32_t);
    double iterate_m(Cmp&, const Cmp&);
    double iterate_j(Cmp&, const Cmp&, const JFunc&);
    int mandelbrot(opts::Settings&);
    int julia(opts::Settings&);
}

#endif
