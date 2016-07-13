#include <stdint.h>

#ifndef HXX_COLORMAPPING
#define HXX_COLORMAPPING
class CRGBColor {
public:
    CRGBColor() { }
    CRGBColor( uint8_t _r, uint8_t _g, uint8_t _b ) {
        r = _r; g = _g; b = _b;
    }

    uint8_t r, g, b;

};

class CColorMapping {
public:
    virtual ~CColorMapping() { }

    virtual CRGBColor Map( unsigned int count ) = 0;
};

class FractintMapFile : public CColorMapping
{
public:
    FractintMapFile() { }
    virtual ~FractintMapFile() { }
    bool LoadMapFile( const char *s );

    virtual CRGBColor Map( unsigned int count ) {
        return m_colors[count];
    }
private:
    CRGBColor m_colors[256];
};
#endif
