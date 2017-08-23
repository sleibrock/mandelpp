/*
 * resolutions.h
 *
 * Includes struct and a static array of all available resolutions
 * for the program. Supports most 4:3 and 16:9 resolution
 * viewports.
 *
 */

#ifndef _RESOLUTION_HEADER
#define _RESOLUTION_HEADER

#define RESOLUTION_COUNT   23


/*
 * The struct containing information about viewport rendering
 */
typedef struct reso_t
{
    const char*  name;
    const uint32_t width;
    const uint32_t height;
} reso_t;

// Resolutions available to the program
// Width must always be larger than height for landscape aspect
static reso_t all_resolutions[RESOLUTION_COUNT] =
{
    // standard resolution outputs
    {"480p",       640,    480},
    {"720p",      1280,    720},
    {"768p",      1024,    768},
    {"900p",      1600,    900},
    {"1080p",     1920,   1080},
    {"1440p",     2560,   1440},

    // highly deadly resolutions
    {"4k",        3840,   2160},
    {"8k",        7680,   4320},
    {"16k",      15360,   8640},  // ~400mb
    {"32k",      30720,  17280},  // ~1.6gb !!!!
    {"64k",      61440,  34560},  // ~6gb, god help us all

    // Apple resolutions
    {"iphoneSE",  1136,    640},
    {"iphone5",   1136,    640},
    {"iphone7",   1134,    750},
    {"iphone7+",  2208,   1242},
    {"ipadMini",  2048,   1536},
    {"ipadAir",   2048,   1536},
    {"ipadPro10", 2224,   1668},
    {"ipadPro12", 2732,   2048},
    {"iwatch1",    340,    272},
    {"iwatch2",    390,    312},

    // unconventional rendering resolutions 
    {"twitter",   1024,    576},
    {"instagram", 1024,    768},
};


/*
 * Print out a list of all resolutions to stdout.
 * Used when the user gives an invalid resolution
 */
void print_supported_resolutions()
{
    std::cout << "Supported resolutions list: " << std::endl << std::endl;

    for(unsigned int c=0; c < RESOLUTION_COUNT; c++)
    {
        std::cout << "  * " << all_resolutions[c].name << ", "
            << all_resolutions[c].width << "x" << all_resolutions[c].height << std::endl;
    }
};
#endif
