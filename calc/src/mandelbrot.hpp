#include "point.hpp"

namespace calc::mandelbrot {
	class MandelPoint : Point {
		public:
			MandelPoint(int x, int y);
			MandelPoint(calc::Point*);
			void calc(unsigned int maxIters);
			bool included;
			int iters;
			double magnitude;
		private:
	};
}
			
	

