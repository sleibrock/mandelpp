#include "include/mandelbrot.h"

int main(int argc, char **argv)
{

    srand(time(0));
    opts::Settings render_settings = opts::parse(argc, argv);

    render_image(render_settings);

    /*
    Cmp a = Cmp(0, 4);
    Cmp b = Cmp(3, -7);

    std::cout << "A is " << a << std::endl;
    std::cout << "B is " << b << std::endl;

    std::cout << "A+B = " << (a+b) << std::endl;
    std::cout << "A-B = " << (a-b) << std::endl;

    std::cout << "A*B = " << (a*b) << std::endl;
    std::cout << "A/B = " << (a/b) << std::endl;
    */

    return 0;
}
