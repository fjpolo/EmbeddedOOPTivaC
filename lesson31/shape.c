#include "shape.h"

void shape_constructor(Shape * const me, int16_t x0, int16_t y0){
    me->x = x0;
    me->y = y0;
}

void shape_moveBy(Shape * const me, int16_t dx, int16_t dy){
    me->x += dx;
    me->y += dy;
}

int16_t shape_distanceFrom(Shape const * const me, Shape const * other){
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

/*Virtual calls - Late binding*/
void Shape_draw_vcall(Shape const * const me){
	//me->vptr->draw(me);
	(*me->vptr->draw)(me);
}
	
uint32_t Shape_area_vcall(Shape const * const me){
	//return me->vptr->area(me);
	return (*me->vptr->area)(me);
}