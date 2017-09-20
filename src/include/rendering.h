#ifndef _RENDERING_H
#define _RENDERING_H

#include <iostream>
#include <fstream>
#include <functional>

#include "complex.h"
#include "opts.h"
#include "functions.h"

namespace render
{
    // A julia function represented as a Lambda type
    typedef std::function<Cmp(Cmp&, const Cmp&)> JFunc;

    
    std::ofstream* create_image(std::string, opts::Settings&);
    double iterate_m(Cmp&, const Cmp&);
    double iterate_j(Cmp&, const Cmp&, const funcs::JFunc_t&);
    int mandelbrot(opts::Settings&);
    int julia(opts::Settings&);
}

#endif
