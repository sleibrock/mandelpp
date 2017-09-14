/*
 * colors.h
 *
 * All colors available through the program options
 * and functions surrounding interpolation between them
 */
#ifndef _COLORS_H
#define _COLORS_H

#include <stdint.h>
#include <cmath>

#define COLORMAP_COUNT  3

namespace colors
{
    
    /*
     * Struct to hold basic R/G/B info as doubles
     */
    typedef struct rgb_t
    {
        double r;
        double g;
        double b;
    } rgb_t;


    // All of the colors available to use
    //extern colormap_t all_colormaps[COLORMAP_COUNT];
    
    
    // basic functions
    //void     print_color_info();
    double   lerp(double, double, double);
    uint8_t  flatten(double);

}
#endif
