#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

/*Circle class*/
class Circle : public Shape{	// Inherit Shape class
private:
    uint16_t radius;

public:
	
	Circle(int16_t x0, int16_t y0,
											uint16_t r0);
	virtual void draw(void) const;
	virtual uint32_t area(void) const;
};

#endif // CIRCLE_H
