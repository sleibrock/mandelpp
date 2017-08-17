# Mandelbrot Set Generator

A Mandelbrot Set rasterizing tool to output images of Mandelbrot Sets.

Usage:
```
-h, --help     Print out these options
-s, --size     Select a resolution size to use
-x, --real     Set the initial real value
-y, --imag     Set the initial imaginary value
-c, --colors   Set which color gradient to use
-z, --zoom     Set the zoom level
-r, --random   Enable random point/zoom selection
-v, --verbose  Program will print more text at runtime 
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

# Requirements

Compiles, tested and runs on the following:

* GCC 5.3.0
* Make 3.82.90
* Windows 10, Linux 3.16
