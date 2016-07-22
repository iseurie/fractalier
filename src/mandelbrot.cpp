#include <cmath>
#include <complex> 
#include <vector> 
#include <thread>
#include <iostream>
#include <mutex>
#include <cstring>
#include <png.h>

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

unsigned int Mandelbrot::eval(const complex<double>& c, unsigned int d) {
    unsigned int ret = 0;
    complex<double> z(0.0);
    while(norm(z) < 4.0 && ret < d) {
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

bool Mandelbrot::WritePNGFile (const char *file_name, 
    const std::vector<std::vector<unsigned int>>& v,
    png_colorp palette) {
    bool ret = false;
    png_bytep *row_pointers = 0;
    png_structp png_ptr = 0;
    png_infop info_ptr = 0;
    int height = v.size();
    int width = v[0].size();

    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp) return false;

    row_pointers = (png_bytep *) malloc( height*sizeof(*row_pointers) );
    if ( ! row_pointers) goto Error;
    memset( row_pointers, 0, height*sizeof(*row_pointers) );
    for ( int row = 0; row < height; row++ ) {
        row_pointers[row] = (png_bytep) malloc( width*sizeof(uint8_t) );
        if ( NULL == row_pointers[row] ) goto Error;
        for ( int col = 0; col < width; col++ ) {
            row_pointers[row][col] = (uint8_t) v[row][col];
        }
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) goto Error;

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) goto Error;

    png_set_PLTE( png_ptr, info_ptr, palette, 256 );

#if 0
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during init_io");
#endif

    png_init_io(png_ptr, fp);

#if 0
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during writing header");
#endif

    png_set_IHDR(png_ptr, info_ptr, v[0].size(), v.size(),
             8, PNG_COLOR_TYPE_PALETTE, PNG_INTERLACE_NONE,
             PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);

#if 0
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during writing bytes");
#endif

    png_write_image(png_ptr, row_pointers);

#if 0
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during end of write");
#endif

    png_write_end(png_ptr, NULL);

    ret = true;

Error:
    if ( png_ptr ) {
        png_destroy_write_struct( &png_ptr, &info_ptr );
    }
    if ( row_pointers ) {
        for (unsigned int y=0; y<height; y++)
            free(row_pointers[y]);
        free(row_pointers);
    }

    if ( fp ) fclose(fp);
    return ret;
}

void Mandelbrot::eval_srt(vector<vector<unsigned int>>& map, 
        complex<double>& min, complex<double>& mag, unsigned int& d,
        mutex& rMapMutex, mutex& frameMutex) {
    rMapMutex.lock();
    int h = map.size();
    int w = map[0].size();
    rMapMutex.unlock();
    for(unsigned int row = 0; row < h; ++row) {
        for(unsigned int col = 0; col < w; ++col) {
            rMapMutex.lock();
            if(map[row][col] == 0) {
                rMapMutex.unlock();
                frameMutex.lock();
                double imag = min.imag() + row * (mag.imag() / h);
                double real = min.real() + col * (mag.real() / w);
                frameMutex.unlock();
                rMapMutex.lock();
                map[row][col] = eval(complex<double>(real, imag), d);
                rMapMutex.unlock();
            }
        }
    }
}

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

vector<vector<unsigned int>> Mandelbrot::render(unsigned int w, unsigned int h,
        unsigned short max_threads) {
    vector<vector<unsigned int>> map;
    mutex render_map_mutex;
    mutex frame_prop_mutex;
    map.resize(h, vector<unsigned int>(w));
    thread threads[max_threads];
    unsigned short currentThreads = 0;

    cout << "Mandelbrot::render: Spawning "
            << max_threads << " evaluator subroutines" << endl;

    while(currentThreads < max_threads) {
        threads[currentThreads] = thread(ref(eval_srt), 
                ref(map), ref(min), ref(mag), ref(maxIters), 
                ref(render_map_mutex), ref(frame_prop_mutex));
        if(!threads[currentThreads].joinable()) {
            cerr << "Mandelbrot::render: Failed to spawn child evaluator thread" 
                    << " (index " << currentThreads << ')' << endl;
        } else {
            threads[currentThreads].join();
            ++currentThreads;
        }
    }
    return map;
} 
