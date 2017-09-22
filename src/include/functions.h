/*
 * functions.h
 *
 * Describes the function signatures used for computing julia sets
 * and contains the array header for function pointers
 */
#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "complex.h"

#ifdef DGMP
#else

namespace funcs
{
    extern const uint32_t JFUNC_COUNT;

    typedef void (*JFunc_t)(Cmp&, const Cmp&);

    typedef struct JuliaFunc
    {
        const char*   name;
        const JFunc_t func;
    } JuliaFunc;

    void _z_squared(Cmp& z, const Cmp& c);
    void _z_cubed(Cmp& z, const Cmp& c);

    void print_all();

    extern const JuliaFunc all[];
}
#endif


#endif
// end
