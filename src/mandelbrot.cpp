#include <cmath>
#include <complex> 
#include <vector> 
#include "mandelbrot.hpp"

using namespace std;

Mandelbrot::Mandelbrot(const complex<double>& anchor, const complex<double>& extent, unsigned int depth) {
	this->min = anchor;
	this->mag = extent;
	this->maxIters = depth;
}

unsigned int Mandelbrot::eval(const complex<double>& c) {
	//sample the given complex coordinate.
	unsigned int ret = 0;
	complex<double> z(0.0);
	while(norm(z) < 4.0 && ret < maxIters) {
		z = z * z + c;
		++ret;
	}
	return ret;
}

/*
void Mandelbrot::render(const unsigned int* p, unsigned int w, unsigned int h) {
	for(unsigned int row = 0; row < h; ++row) {
		double imag = min.imag() + row * (mag.imag() / h); 
		//'unsigned int* rowp = *p + row * w
		unsigned int* rowp = &p[row * w];
		for(unsigned int col = 0; col < w; ++col) {
			double real = min.real() + col * (mag.real() / w);
			rowp[col] = eval(complex(real, imag);
		}
	}
}
*/

vector<vector<unsigned int>> Mandelbrot::render(unsigned int w, unsigned int h) {
	vector<vector<unsigned int>> map;
	map.resize( h, vector<unsigned int>(w) );
	for(unsigned int row = 0; row < h; ++row) {
		/* determine the imaginary value of row 'row,' dividing the
		 * extense of the parent fractal region by the rendering height
		 * and thus coercing the more precise points of the parent 
		 * fractal abstract to the scale of the render map. */

		double imag = min.imag() + row * (mag.imag() / h);  
		for(unsigned int col = 0; col < w; ++col) {
			double real = min.real() + col * (mag.real() / w);
			map[row][col] = eval(complex<double>(real, imag));
		}
	}
	return map;
}
