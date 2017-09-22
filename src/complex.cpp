/*
 * complex.cpp
 * 
 * All Complex class logic and such goes here
 * if the DGMP macro is enabled (if libgmp is on the system)
 * then use those #if macros to create GMP-specific code
 * using the mpf_t type
 */

#include <iostream>
#include "include/complex.h"

/*
 * GMP code must be handled differently since every mpf_t
 * is a struct, and allocations must be handled very carefully.
 * Instead of doing tons of pass-by-value/refs, computations
 * should instead mutate an exterior mpf_t pointer so that
 * initializing and destructuring mpf_t's is not a thing
 * the Complex class should have to do.
 *
 * It is better to avoid lots and lots of inits/destructs
 * as to avoid malloc overhead.
 * 
 * Operator overloading will possibly not work as the return
 * types will not be similar since we are not doing simple
 * return by values/refs/etc. GMP types have to be carefully
 * handled.
 *
 * The overall Complex class API may be different because of
 * how GMP types have to be handled. Rudimentary things
 * like less-than or absolute value will be a lot different
 * in the GMP version of the class.
 *
 * GOAL: Complex Class contains two mpf_t types representing
 *       the real and imaginary values of a Complex number.
 *       Arithmetic results should be tossed to an exterior
 *       mpf_t type for better performance
 */


/*
 * No-value constructor
 */
Cmp::Cmp()
{
    // null value
    real = 0.0;
    imag = 0.0;
}


/*
 * Constructor setting both properties to the arg
 */
Cmp::Cmp(double value)
{
    real = value;
    imag = value;
}

/*
 * Constructor for two values
 */
Cmp::Cmp(double r, double i)
{
    real = r;
    imag = i;
}

/*
 * Destructor, does nothing for native version
 * No heap allocs are made with the double version of Cmp
 */
Cmp::~Cmp(){}


void Cmp::add(const Cmp& other)
{
    real = real + other.real;
    imag = imag + other.imag;
}


void Cmp::sub(const Cmp& other)
{
    real = real - other.real;
    imag = imag - other.imag;
}


void Cmp::mul(const Cmp& other)
{
    // store one num temporarily to avoid affecting the other
    double r = (real * other.real) - (imag * other.imag);
    imag     = (imag * other.real) + (real * other.imag);
    real     = r;
}


void Cmp::div(const Cmp& other)
{
    // store one side again to avoid conflicts
    double d = (other.real*other.real) + (other.imag*other.imag);
    double r = ((real*other.real)+(imag*other.imag))/d;
    imag     = ((imag*other.real)-(real*other.imag))/d;
    real     = r;
}

/*
 * Adds a double to the object's real value
 * (in these cases we assume the given double
 * can only be considered a Real value)
 */
void Cmp::add(double value)
{
    real = real + value; 
}

/*
 * Subs a double from the object's real value
 */
void Cmp::sub(double value)
{
    real = real - value;
}


/*
 * Multiplies both properties by a scalar
 */
void Cmp::mul(double scalar)
{
    real = real * scalar;
    imag = imag * scalar;
}


/*
 * Divides both properties by a scalar
 */
void Cmp::div(double scalar)
{
    real = real / scalar;
    imag = imag / scalar;
}

void Cmp::neg()
{
    real = -real;
    imag = -imag;
}


/*
 * Complex conjugate (invert)
 */
Cmp Cmp::conjugate()
{
    Cmp a;
    a.real = real * (-1.0);
    a.imag = imag * (-1.0);
    return a;
}

/*
 * Length2 method (real^2 + imag^2)
 * This is cheaper to do since it doesn't
 * involve calculating square roots
 */
#ifdef DGMP
#else
double Cmp::length2()
{
    return (real*real) + (imag*imag);
}
#endif


/*
 * Debug output method using iostream
 */
std::ostream& operator<<(std::ostream& fout, const Cmp& a)
{
    fout << "Complex(" << a.real << ", " << a.imag << ")";
    return fout;
}

// end
