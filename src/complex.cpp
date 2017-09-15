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
 *
 */
Cmp::Cmp()
{
}


/*
 *
 */
Cmp::Cmp(double value)
{
}

/*
 *
 */
Cmp::Cmp(double r, double i)
{
}

/*
 *
 */
Cmp::~Cmp()
{

}
#else

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
    real = (real * other.real) - (imag * other.imag);
    imag = (imag * other.real) + (real * other.imag);
    return *this;
}


/*
 *
 */
Cmp& Cmp::operator/=(const Cmp& other)
{
    double denom = (other.real * other.real) + (other.imag * other.imag);
    real = ((real * other.real) + (imag * other.imag)) / denom;
    imag = ((imag * other.real) - (real * other.imag)) / denom;
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
void Cmp::length2(mpf_t* res)
{

}
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
