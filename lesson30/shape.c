#include "shape.h"

void shape_constructor(shape_t * const me, int16_t x0, int16_t y0){
    me->x = x0;
    me->y = y0;
}

void shape_moveBy(shape_t * const me, int16_t dx, int16_t dy){
    me->x += dx;
    me->y += dy;
}

int16_t shape_distanceFrom(shape_t const * const me, shape_t const * other){
    int16_t dx = me->x - other->x;
    int16_t dy = me->y - other->y;
    if( dx<0 ){
        dx = -dx;
    }
    if( dy<0){
        dy = -dy;
    }
    return (dx + dy);
}
