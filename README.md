# Mandelbrot and Julia Set Generators

`mandelpp` is a project aimed at creating high-quality Mandelbrot and Julia set images. It is currently written in C++.

Things `mandelpp` does:
* Craft a fractal around a given complex number
* Supports 4:3, 16:9 and other types of resolutions
* Aspect ratio is completely maintained
* Very high magnification/zoom levels
* Outputs images in Netbpm (PPM) file format

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
* ~~Support an array of functions for the Julia program~~
* Update Make process to detect `gmp.h` on the target system
* Add macro'd code for GMP arithmetic support
* Implement a new coloring system and smooth shading (norm iter count)
* ~~Ensure all library code is wrapped in easy-to-use namespaces~~
* Add a `.travis.yml` file for CI builds and testing
* Create documentation and set up a `gh-pages` branch

# Requirements

Compiles, tested and runs on the following:

* GCC 5.3.0
* Make 3.82.90
* OS: Windows (w/ Cygwin/MinGW), Linux 3.16
