/*
 * functions.cpp
 *
 * All core code regarding Julia set functions
 */
#include "include/complex.h"
#include "include/functions.h"

namespace funcs
{
    const uint32_t JFUNC_COUNT = 2;

    /*
     * A basic z^2 + c function
     */
    Cmp _z_squared(Cmp& z, const Cmp& c)
    {
        return (z*z) + c;
    }


    /*
     * A basic z^3 + c function
     */
    Cmp _z_cubed(Cmp& z, const Cmp& c)
    {
        return (z*z*z) + c;
    }

    // defines all functions available for Julia Set rendering
    const JuliaFunc all[] =
    {
        {"z^2+c", &_z_squared},
        {"z^3+c",   &_z_cubed},
    };


    /*
     * Prints out all available functions to use
     */
    void print_all()
    {
        std::cout << "Available Julia Set functions:" << std::endl;

        for(uint32_t j=0; j < JFUNC_COUNT; j++)
            std::cout << "  * " << all[j].name << std::endl;

        std::cout << std::endl;
    }
}
