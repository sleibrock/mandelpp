#ifndef _MANDELBROT_H
#define _MANDELBROT_H

#define MAX_ITERS 255.0

#include "complex.h"
#include "opts.h"

double iterate(Cmp&, Cmp&);
int mandelbrot_image(opts::Settings&);
int main(int, char**);

#endif
