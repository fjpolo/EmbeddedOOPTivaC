#ifndef SHAPE_H
#define SHAPE_H

#include <stdint.h>

/*Shape CLASS*/

/*Shape attributes*/
typedef struct{
	struct ShapeVtable const *vptr;	/*Virtual pointer*/
	/**/
  int16_t x; // x-coordinate of shape's pisition
  int16_t y; // y-coordinate of shape's pisition
}Shape;

/*Virtual Vector table*/
struct ShapeVtable{
	void (*draw)(Shape const * const me);
	uint32_t (*area)(Shape const * const me);
};

/*Encapsulation!!*/
/*Shape operations*/
void shape_constructor(Shape * const me, int16_t x0, int16_t y0);
void shape_moveBy(Shape * const me, int16_t dx, int16_t dy);
int16_t shape_distanceFrom(Shape const * const me, Shape const * other);

/*Virtual calls - Late binding*/
#define SHAPE_DRAW_VCALL(me) (*(me)->vptr->draw)((me))
#define SHAPE_AREA_VCALL(me) (*(me)->vptr->area)((me))

#endif // SHAPE_H
