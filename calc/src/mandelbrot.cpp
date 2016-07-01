#include "mandelbrot.hpp"
#include "point.hpp"

using namespace std;
using namespace calc;

namespace calc::mandelbrot {
	MandelPoint::MandelPoint (Point* coords) : Point(coords->a, coords->b) {
		this->a = coords->a;
		this->b = coords->b;
		iters = 0;
		included = false;
		magnitude = 0.0;
	}
	
	MandelPoint::MandelPoint(int x, int y) : Point(x, y) {
		this->a = x;
		this->b = y;
		iters = 0;
		included = false;
		magnitude = 0.0;
	}
	
	void MandelPoint::calc(unsigned int maxIters) {
		double x, y, xx, yy;
		x = y = xx = yy = 0.0;
		for(iters < maxIters; ++iters; ) {
			y = (x + x) * y + b;
			x = xx - yy + a;
			yy = y * y;
			xx = x * x;
			//Break and set point meta-data when iterations are depleted, or when the point is determined not to be included.
			if ((magnitude = xx + yy) >= 2) {
				included = true;
			} else {
				included = false;
			}
			
		}
	}
}
