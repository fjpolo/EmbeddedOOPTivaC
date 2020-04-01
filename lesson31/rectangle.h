#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

/*Rectangle_t attributes*/
typedef struct{
    Shape super; // Inherited Shape
    /**/
    uint16_t width;
    uint16_t height;
}Rectangle_t;

/*Rectangle_t Operations*/
void Rectangle_ctor(Rectangle_t * const me, 
                    int16_t x0, int16_t y0,
                    uint16_t w0, uint16_t h0);
void Rectangle_draw(Rectangle_t const * const me);
uint32_t Rectangle_area(Rectangle_t const * const me);

#endif // RECTANGLE_H
