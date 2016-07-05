#include <iostream>
#include <array>
#include <vector>

#include <png.h>

#include "colormapping.hpp"
#include "mandelbrot.hpp"

using namespace std;

bool
WritePNGFile( 
    const char *file_name, 
    const vector<vector<unsigned int>>& v,
    png_colorp palette
)
{
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


int
main()
{
    Mandelbrot canonical( std::complex<double>( -2.2, -1.7 ), std::complex<double>( 3.4, 2.9 ), 255 ); 

    auto imageIterations = canonical.render( 1024, 768 );

#if 0
    for ( unsigned int row = 0; row < imageIterations.size(); row++ ) {
        for ( unsigned int col = 0; col < imageIterations[row].size(); col++ ) {
            printf( "%5d", imageIterations[row][col] );
        }
        printf( "\n" );
    }
#endif

    FractintMapFile m;
    if ( ! m.LoadMapFile( "blues.map" ) ) {
        goto Error;
    }
    png_color palette[256];

    for ( int i = 0; i < 256; i++ ) {
        palette[i].red = m.Map(i).r;
        palette[i].green = m.Map(i).g;
        palette[i].blue = m.Map(i).b;
    }
    WritePNGFile( "test.png", imageIterations, palette );
#if 0

    for ( unsigned int row = 0; row < imageIterations.size(); row++ ) {
        for ( unsigned int col = 0; col < imageIterations[row].size(); col++ ) {
            printf( "%02X", m.Map(imageIterations[row][col]).b );
        }
        printf( "\n" );
    }
#endif

    return 0;
Error:
    return 1;
}

