# Mandelbrot and Julia Set Generators

`mandelpp` is a project aimed at creating high-quality Mandelbrot and Julia set images. It is currently written in C++ for performance. There are no dependencies other than a C++11 supported compiler. The project aims to support GNU Multiprecision, but it's not required to compile.

Usage:
```
-h --help     Print out these options
-s --size     Select a resolution size to use
-x --real     Set the initial real value
-y --imag     Set the initial imaginary value
-c --colors   Set which color gradient to use
-z --zoom     Set the zoom level
-r --random   Enable random point/zoom selection
-v --verbose  Program will print more text at runtime
```

# Examples

![](https://raw.githubusercontent.com/sleibrock/mandelpp/master/docs/whole_720.png)
![](https://raw.githubusercontent.com/sleibrock/mandelpp/master/docs/closeup.png)

# Downloading and Building

Use Git to clone the repository, and use GNU/Make to build the project.
```
git clone https://github.com/sleibrock/mandelpp && cd mandelpp
make
```

# Todo's

* ~~Implement a class-based approach to Complex arithmetic~~
* Support an array of functions for the Julia program
* Update Make process to detect `gmp.h` on the target system
* Add macro'd code for GMP arithmetic support
* Implement a new coloring system and smooth shading (norm iter count)
* Ensure all library code is wrapped in easy-to-use namespaces
* Add a `.travis.yml` file for CI builds and testing
* Create documentation and set up a `gh-pages` branch

# Requirements

Compiles, tested and runs on the following:

* GCC 5.3.0
* Make 3.82.90
* Windows 10, Linux 3.16
