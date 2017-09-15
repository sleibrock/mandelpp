#ifndef _JULIA_H
#define _JULIA_H

#include "opts.h"
#include "complex.h"

double iterate(Cmp&, const Cmp&);
int julia_image(opts::Settings&);
int main(int, char**);

#endif
