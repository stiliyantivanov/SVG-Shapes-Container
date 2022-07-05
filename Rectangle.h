#pragma once

#include "Figure.h"

class Rectangle : public Figure {
private:
	double width, height;
	Point point;
public:
	Rectangle();
	Rectangle(const Point&, const double&, const double&, const Colour&);
	Rectangle(const Rectangle&) = default;
	Rectangle& operator=(const Rectangle&) = default;
	~Rectangle() = default;

	double getWidth() const;
	double getHeight() const;
	Point getPoint() const;

	virtual double perimeter() const override;
	virtual double area() const override;
	virtual void print() const override;
	virtual bool containsFigure(const Figure*) const override;
	virtual bool containsPoint(const Point&) const override;
	virtual Figure* clone() const override;
	virtual void translate(const double&, const double&) override;
};