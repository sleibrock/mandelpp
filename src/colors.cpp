/*
 * colors.cpp
 *
 * Library for handling color shading and interpolation,
 * as well as ensuring data passed through is the proper type
 */

#include <iostream>
#include <cstdint>
#include "include/colors.h"

namespace colors
{

    /*
    void print_color_info()
    {
        std::cout << "Color schemes available: " << std::endl;
        
        for(uint32_t c=0; c < COLORMAP_COUNT; c++)
            std::cout << " -- " << all_colormaps[c].name << std::endl;
    }
    */
    
    
    /*
    * Linear interpolation between two doubles (inline for performance)
    */
    double lerp(double a, double b, double t)
    {
        return (1.0 - t) * a + t * b;   
    }
    

    /*
    *  Convert a double to a uint8_t type for writing to file
    */
    uint8_t flatten(double x)
    {
        return (uint8_t)floor(x);
    }

}

// end

