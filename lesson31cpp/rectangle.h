#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

/*Rectangle class*/
class Rectangle : public Shape{	// Inherit Shape class
private:
    uint16_t width;
    uint16_t height;

public:
	
	Rectangle(int16_t x0, int16_t y0,
											uint16_t w0, uint16_t h0);
	virtual void draw(void) const;
	virtual uint32_t area(void) const;
};

#endif // RECTANGLE_H
