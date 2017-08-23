/*
 * colors.h
 *
 * All colors available through the program options
 * and functions surrounding interpolation between them
 */
#ifndef _COLORS_H
#define _COLORS_H

#define COLORMAP_COUNT  3


/*
 * A basic double-based RGB triplet struct
 * Used mostly with the gradients
 */
typedef struct color_t
{
    double r;
    double g;
    double b;
} color_t;


/*
 * Used to create various n-rank gradients
 */
typedef struct colormap_t
{
    const char* name;
    const color_t color1;
    const color_t color2;
} colormap_t;


/*
 * All color maps available for the program
 */
static colormap_t all_colormaps[COLORMAP_COUNT] =
{
    {"b&w",    {  0.0,   0.0,   0.0}, {190.0, 190.0, 190.0}},
    {"red",    {  0.0,  20.0,  30.0}, {210.0,   0.0,  10.0}},
    {"blue",   {  0.0,  24.0, 104.0}, {163.0, 255.0, 252.0}},
};


/*
 * Linear interpolation between two doubles (inline for performance)
 */
inline double lerp(double a, double b, double t)
{
    return (1.0 - t) * a + t * b;   
}

/*
 *  Convert a double to a uint8_t type for writing to file
 */
inline uint8_t flatten(double x)
{
    return (uint8_t)floor(x);
}

/*
 * Gradient class accepts a number of color constants
 * and later receives indices to use an arbitrary-sized
 * color palette.
 *
 * Currently only accepts two points and uses linear
 * interpolation to create the color palette
 */
class Gradient
{
public:
    const color_t& left;
    const color_t& right;
    Gradient(const color_t& a, const color_t& b): left(a), right(b) {};

    void reset(color_t* storage)
    {
        storage->r = 0.0;
        storage->g = 0.0;
        storage->b = 0.0;
    }

    /*
     *  Pick a color index X from a range of indices (N indices)
     */
    void pick(double x, double n, color_t* storage)
    {
        double t = x / n;
        storage->r = lerp(left.r, right.r, t);
        storage->g = lerp(left.g, right.g, t);
        storage->b = lerp(left.b, right.b, t);
    }

    /*
     * Similar to above except it interpolates between two indices
     * used with the Normalized Iteration Count
     */
    void interp(double x, double n, double p, color_t* storage)
    {
        double t1  = x / n;
        double t2  = (x+1) / n;
        storage->r  = lerp(lerp(left.r, right.r, t1), lerp(left.r, right.r, t2), p);
        storage->g  = lerp(lerp(left.g, right.g, t1), lerp(left.g, right.g, t2), p);
        storage->b  = lerp(lerp(left.b, right.b, t1), lerp(left.b, right.b, t2), p);
    }
};

#endif
