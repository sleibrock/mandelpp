/*
 * Complex Class
 * Macro included to determine whether to use GMP types or not
 * Because std::complex isn't meant for GMP's mpf_t types,
 * we will have to roll a custom class that supports mpf_t ops
 * The DGMP macro will inform us whether libgmp is supported
 * in the compiler
 */ 

#ifndef _CMP_H
#define _CMP_H

#include <cmath>
#include <iostream>

class Cmp
{
public:

#ifdef DGMP
    mpf_t real, imag;
#else
    double real, imag;
#endif

    // inits / destructs
    Cmp();
    Cmp(double);
    Cmp(double, double);
    ~Cmp();

    // math ops
    Cmp    operator+(const Cmp&);
    Cmp    operator-(const Cmp&);
    Cmp    operator*(const Cmp&);
    Cmp    operator/(const Cmp&);

    Cmp&   operator+=(const Cmp&);
    Cmp&   operator-=(const Cmp&);
    Cmp&   operator*=(const Cmp&);
    Cmp&   operator/=(const Cmp&);

    // methods
    Cmp    conjugate();

#ifdef DGMP
    void   length2(mpf_t*);
#else
    double length2();
#endif

    // debug
    friend std::ostream& operator<<(std::ostream&, const Cmp&); 
};

#endif // end include header

//end
