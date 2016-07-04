#include <iostream>
#include <array>

#include "colormapping.hpp"
#include "Mandelbrot.hpp"

void
main()
{
    Mandelbrot canonical( std::complex<double>( -2.2, -1.7 ), std::complex<double>( 3.4, 2.9 ), 255 );
    

    auto imageIterations = canonical.render( 16, 9 );

    for ( unsigned int row = 0; row < imageIterations.size(); row++ ) {
        for ( unsigned int col = 0; col < imageIterations[row].size(); col++ ) {
            printf( "%5d", imageIterations[row][col] );
        }
        printf( "\n" );
    }

    FractintMapFile m;
    if ( m.LoadMapFile( "blues.map" ) ) {
        for ( unsigned int row = 0; row < imageIterations.size(); row++ ) {
            for ( unsigned int col = 0; col < imageIterations[row].size(); col++ ) {
                printf( "%02X", m.Map(imageIterations[row][col]).b );
            }
            printf( "\n" );
        }
        
    }
}
