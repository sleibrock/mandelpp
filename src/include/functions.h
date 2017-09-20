/*
 * functions.h
 *
 * Describes the function signatures used for computing julia sets
 * and contains the array header for function pointers
 */
#include <iostream>

#include "complex.h"

#ifdef DGMP
#else

namespace funcs
{
    typedef Cmp (*JFunc_t)(Cmp&, const Cmp&);

    Cmp _z_squared(Cmp& z, const Cmp& c);
    Cmp _z_cubed(Cmp& z, const Cmp& c);
    
    extern const JFunc_t all[];
}
#endif

// end
