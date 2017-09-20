#include <iostream>

#include "include/complex.h"
#include "include/functions.h"

namespace funcs
{

    Cmp _z_squared(Cmp& z, const Cmp& c)
    {
        return (z*z) + c;
    }


    Cmp _z_cubed(Cmp& z, const Cmp& c)
    {
        return (z*z*z) + c;
    }

    const JFunc_t all[]=
    {
        &_z_squared,
        &_z_cubed,
    };

    

}
