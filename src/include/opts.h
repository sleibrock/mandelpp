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
#define M_COMMANDS              10
#define J_COMMANDS              10
#define ASCII_LINES              9
#define DEFAULT_ZOOM           0.5
#define DEFAULT_RE            -0.7
#define DEFAULT_IM             0.0

// define macros for random value creation
#define RAND_ZOOM_HIGH        10.0
#define RANDOM(LOW, HIGH) (LOW + (rand() * (HIGH - LOW)))


namespace opts
{
    // Different arrays will have to be made for
    // the Julia and Mandelbrot programs
    extern const        char*    mandel_art[ASCII_LINES];
    extern const struct option   mlong_opts[M_COMMANDS];
    extern const        char*   mshort_opts;
    extern const        char*  moption_help[M_COMMANDS];

    extern const        char*     julia_art[ASCII_LINES];
    extern const struct option   jlong_opts[J_COMMANDS];
    extern const        char*   jshort_opts[J_COMMANDS];
    extern const        char*  joption_help[J_COMMANDS]; 

    void print_mandel_info();
    void print_julia_info();

    class Settings
    {
    public:
        // resolution and filename
        // char* fname;
        const reso::rect_t* res;

        // program flags
        uint8_t verbose,   random;

        // dimensional values for iterating later
        double  init_real,  init_imag, zoom;
        double  span_x,     span_y;
        double  topleft_x,  topleft_y;
        double  botright_x, botright_y;
        double  inc_re,     inc_im;
        double  init_zr,    init_zi; 
        
        Settings(uint8_t, uint8_t, double, double, double, const reso::rect_t*);
        void display_info();
    };

    Settings mparse(int, char**);
    Settings jparse(int, char**);
}

#endif
