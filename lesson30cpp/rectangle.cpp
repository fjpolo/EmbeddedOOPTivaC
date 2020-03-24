#include "rectangle.h"

Rectangle::Rectangle(int16_t x0, int16_t y0,
                    uint16_t w0, uint16_t h0)
										:Shape(x0,y0),
										width(w0),
										height (h0)
{}


	void Rectangle::draw(void) const{
    // Drawwww
    //
}

uint32_t Rectangle::area(void) const{
    return ( (uint32_t)width * (uint32_t)height );
}
