/*
 * resolutions.cpp
 *
 * Includes all code surrouding various output dimensions
 */
#include <iostream>
#include "include/resolutions.h"


namespace reso
{
    const rect_t all[] =
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
        
        // Apple resolutions (landscape mode of course)
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
    void print_all()
    {
        std::cout << "Supported resolutions list: " << std::endl << std::endl;
        
        for(unsigned int c=0; c < RESOLUTION_COUNT; c++)
        {
            std::cout << "  * " << all[c].name << ", "
                      << all[c].width << "x" << all[c].height << std::endl;
        }
    }

}
    
// end
