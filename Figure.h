#pragma once

#include "Point.h"

enum Shape {
	rectangle,
	circle,
	line
};

enum Colour {
	white,
	black,
	red, 
	green,
	blue,
	yellow,
	orange, 
	purple,
	other
};

class Figure {
protected:
	Shape shape;
	Colour fill;
public:
	Figure() = default;
	Figure(const Figure&) = default;
	Figure& operator=(const Figure&) = default;
	virtual ~Figure() = default;

	Shape getShape() const;
	Colour getFill() const;

	virtual double perimeter() const = 0;
	virtual double area() const = 0;
	virtual void print() const = 0;
	virtual bool containsFigure(const Figure*) const = 0;
	virtual bool containsPoint(const Point&) const = 0;
	virtual Figure* clone() const = 0;
	virtual void translate(const double&, const double&) = 0;
};