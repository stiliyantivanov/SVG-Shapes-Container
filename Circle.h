#pragma once

#include "Figure.h"

class Circle : public Figure {
private:
	double radius;
	Point center;
public:
	Circle();
	Circle(const Point&, const double&, const Colour&);
	Circle(const Circle&) = default;
	Circle& operator=(const Circle&) = default;
	~Circle() = default;

	double getRadius() const;
	Point getCenter() const;

	virtual double perimeter() const override;
	virtual double area() const override;
	virtual void print() const override;
	virtual bool containsFigure(const Figure*) const override;
	virtual bool containsPoint(const Point&) const override;
	virtual Figure* clone() const override;
	virtual void translate(const double&, const double&) override;
};