#include "colormapping.hpp"
#include <stdio.h>

bool
FractintMapFile::LoadMapFile( const char *s )
{
    bool ret = false;
    FILE *f = fopen( s, "r" );
    if  ( ! f ) 
        goto Error;
    for ( int i = 0; i < 256; i++ ) {
        int r, g, b;
        char line[256];
        if ( NULL == fgets( line, 256, f ) ) goto Error;
        if ( 3 != sscanf( line, "%d %d %d", &r, &g, &b ) ) goto Error;
        m_colors[i] = CRGBColor( r, g, b );
    }
    ret = true;
Error:
    fclose( f );
    return ret;
}
