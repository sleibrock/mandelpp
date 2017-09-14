/*
 * This file is used to define generic utilities for the project
 *
 * Contains: 
 *   program version constant
 *   program options and their help messages
 *   render settings struct and other stuffs surrounding it
 *   ascii art!
 */

#ifndef _OPTS_H
#define _OPTS_H

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <getopt.h>
#include <math.h>
#include <string.h>

// local includes
#include "resolutions.h"
#include "colors.h"

#define PROGRAM_VERSION        0.1
#define NUM_COMMANDS            10
#define ASCII_LINES              9
#define DEFAULT_ZOOM           0.5
#define DEFAULT_RE            -0.7
#define DEFAULT_IM             0.0

// define macros for random value creation
#define RAND_ZOOM_HIGH        10.0
#define RANDOM(LOW, HIGH) (LOW + (rand() * (HIGH - LOW)))


namespace opts
{
    extern const        char*  ascii_art[ASCII_LINES];
    extern const struct option long_opts[NUM_COMMANDS];
    extern const        char*  short_opts;
    extern const        char*  option_help[NUM_COMMANDS];

    void print_help_info();

    class Settings
    {
    public:
        uint8_t   verbose;
        uint8_t   random;
        double    init_real;
        double    init_imag;
        double    zoom;
        // char* fname;
        const reso::rect_t*   res;
        
        double    span_x,     span_y;
        double    topleft_x,  topleft_y;
        double    botright_x, botright_y;
        
        double    inc_re, inc_im;
        
        Settings(uint8_t, uint8_t, double, double, double, const reso::rect_t*);
        void display_info();
    };

    Settings parse(int argc, char** argv);
}

#endif
