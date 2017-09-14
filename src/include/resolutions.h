/*
 * resolutions.h
 *
 * Includes struct and a static array of all available resolutions
 * for the program. Supports most 4:3 and 16:9 resolution
 * viewports.
 *
 */

#ifndef _RESOLUTION_H
#define _RESOLUTION_H

#define RESOLUTION_COUNT 23


namespace reso
{
/*
 * The struct containing information about viewport rendering
 */
    typedef struct rect_t
    {
        const char*  name;
        const uint32_t width;
        const uint32_t height;
    } reso_t;
    
    
    extern const rect_t all[RESOLUTION_COUNT];
    void print_all();
    
}
#endif
