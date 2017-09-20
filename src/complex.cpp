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

#ifdef DGMP
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
 * Initialize two mpf_t types inside of the class
 * and set them to zero
 */
Cmp::Cmp()
{
}


/*
 * Init two mpf_t types and set them to whatever the given value is
 */
Cmp::Cmp(double value)
{
}

/*
 * Init two mpf_t types and set them to the supplied args
 */
Cmp::Cmp(double r, double i)
{
}

/*
 * Destroy the two mpf_t types by destructuring them with
 * the respective mpf_t destruction methods in libgmp
 */
Cmp::~Cmp()
{

}

/*
 * Add some complex number to our current one
 */
void Cmp::add(Cmp& other)
{
}

/*
 * Subtract some complex number from our current one
 */
void Cmp::sub(Cmp& other)
{
}

/*
 * Multiply our mpf_t types together on the current object
 */
void Cmp::mul(Cmp& other)
{
}

/*
 * Divide our mpf_t types in the current object
 */
void Cmp::div(Cmp& other)
{
}

void Cmp::length2(mpf_t* res)
{
}

#else // all non-GMP code goes below this line

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

Cmp Cmp::operator+(const Cmp& other)
{
    Cmp r;
    r.real = real + other.real;
    r.imag = imag + other.imag;
    return r; 
    
}

Cmp Cmp::operator-(const Cmp& other)
{
    Cmp r;
    r.real = real - other.real;
    r.imag = imag - other.imag;
    return r;
}

/*
 * Complex multiplication
 * a+bi * c+di = (ac - bd) - (bc + ad)i
 */
Cmp Cmp::operator*(const Cmp& other)
{
    Cmp r;
    r.real = (real * other.real) - (imag * other.imag);
    r.imag = (imag * other.real) + (real * other.imag);
    return r;
}


/*
 * Division op
 * (a+bi) / (c+di) = (ac + bd)/(c^2+d^2) + (bc - ad)/(c^2+d^2)
 */
Cmp Cmp::operator/(const Cmp& other)
{
    Cmp r;
    double denom = (other.real * other.real) + (other.imag * other.imag);
    r.real = ((real * other.real) + (imag * other.imag)) / denom;
    r.imag = ((imag * other.real) - (real * other.imag)) / denom;
    return r;
}


/*
 * Addition assignment
 */
Cmp& Cmp::operator+=(const Cmp& other)
{
    real += other.real;
    imag += other.imag;
    return *this;
}


/*
 * Subtraction assignment
 */
Cmp& Cmp::operator-=(const Cmp& other)
{
    real -= other.real;
    imag -= other.imag;
    return *this;
}


/*
 * Multiplication assignment
 */
Cmp& Cmp::operator*=(const Cmp& other)
{
    // store one num temporarily to avoid affecting the other
    double r = (real * other.real) - (imag * other.imag);
    imag     = (imag * other.real) + (real * other.imag);
    real     = r;
    return *this;
}


/*
 *
 */
Cmp& Cmp::operator/=(const Cmp& other)
{
    // store one side again to avoid conflicts
    double d = (other.real * other.real) + (other.imag * other.imag);
    double r = ((real * other.real) + (imag * other.imag)) / d;
    imag     = ((imag * other.real) - (real * other.imag)) / d;
    real = r;
    return *this;
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

#endif

/*
int main()
{
    Cmp a(-4, 2);
    Cmp b(-3, 8);
    Cmp c = a;
    c += b;
    std::cout << "Hello " << std::endl;
    std::cout << "Result is " << c << std::endl;
    return 0;
}
*/

// end
