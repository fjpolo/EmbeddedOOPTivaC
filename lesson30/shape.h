#ifndef SHAPE_H
#define SHAPE_H

#include <stdint.h>

/*shape_t CLASS*/

/*shape_t attributes*/
typedef struct{
    int16_t x; // x-coordinate of shape's pisition
    int16_t y; // y-coordinate of shape's pisition
}shape_t;

/*Encapsulation!!*/
/*shape_t operations*/
void shape_constructor(shape_t * const me, int16_t x0, int16_t y0);
void shape_moveBy(shape_t * const me, int16_t dx, int16_t dy);
int16_t shape_distanceFrom(shape_t const * const me, shape_t const * other);

#endif // SHAPE_H
