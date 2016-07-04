#include <complex>
#include <vector>

class Mandelbrot {
	public:
		std::complex<double> min;
		std::complex<double> mag;
		unsigned int maxIters;
		Mandelbrot(const std::complex<double>& anchor, //anchor complex coordinate
				const std::complex <double>& extent, //fractal magnitude
				unsigned int depth); //maximum iterations per fractal point
		std::vector<std::vector<unsigned int>>* render(unsigned int w, unsigned int h);
	private:
		unsigned int eval(const std::complex<double>& c); //TODO: Propose namespace evaluation function
};

