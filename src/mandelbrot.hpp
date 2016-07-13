#include <complex>
#include <vector>
#include <array>

#include <png.h>

#ifndef HXX_MANDELBROT
#define HXX_MANDELBROT
class Mandelbrot {
	public:
	    std::complex<double> min;
	    std::complex<double> mag;
            unsigned int maxIters;
	    Mandelbrot(const std::complex<double>& anchor, //anchor complex coordinate
		const std::complex <double>& extent, //fractal magnitude
		unsigned int depth); //maximum iterations per fractal point
		
	    std::vector<std::vector<unsigned int>> render(unsigned int w, unsigned int h);
	bool WritePNGFile(const char* fname, 
        	const std::vector<std::vector<unsigned int>>& rmap, 
                png_colorp palette);
	private:
            unsigned int eval(const std::complex<double>& c);
		
};
#endif
