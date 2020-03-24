#ifndef SHAPE_H
#define SHAPE_H

#include <stdint.h>

/*Shape CLASS*/
class Shape{
  /*Shape attributes*/  
	private:
		
	int16_t x; // x-coordinate of shape's pisition
  int16_t y; // y-coordinate of shape's pisition

	/*Shape operations*/
public:

	Shape(int16_t x0, int16_t y0);
	void moveBy(int16_t dx, int16_t dy);
	uint16_t distanceFrom(Shape const * other) const;

};

#endif // SHAPE_H
