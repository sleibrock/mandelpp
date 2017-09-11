/*
 * Complex Class
 * Macro included to determine whether to use GMP types or not
 * The std::complex does not support native GMP type templating
 * because of the nature of GMP
 */ 

#include <cmath>

#ifndef _CMP_HEADER
#define _CMP_HEADER

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
    Cmp operator+(const Cmp&);
    Cmp operator-(const Cmp&);
    Cmp operator*(const Cmp&);
    Cmp operator/(const Cmp&);

    Cmp& operator+=(const Cmp&);
    Cmp& operator-=(const Cmp&);
    Cmp& operator*=(const Cmp&);
    Cmp& operator/=(const Cmp&);

    // methods
    Cmp conjugate();

    // debug
    friend std::ostream& operator<<(std::ostream&, const Cmp&); 
};

#endif // end include header

//end
