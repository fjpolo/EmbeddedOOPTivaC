#include "rectangle.h"

void Rectangle_ctor(Rectangle_t * const me, 
                    int16_t x0, int16_t y0,
                    uint16_t w0, uint16_t h0){

    shape_constructor(&me->super, x0, y0);
    me->width = w0;
    me->height = h0;
}

void Rectangle_draw(Rectangle_t const * const me){
    // Drawwww
    //
}

uint32_t Rectangle_area(Rectangle_t const * const me){
    return ( (uint32_t)me->width * (uint32_t)me->height );
}
