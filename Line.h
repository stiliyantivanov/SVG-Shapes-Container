#pragma once

#include "Figure.h"

class Line : public Figure {
private:
	Point p1, p2;
public:
	Line();
	Line(const Point&, const Point&, const Colour&);
	Line(const Line&) = default;
	Line& operator=(const Line&) = default;
	~Line() = default;

	Point getP1() const;
	Point getP2() const;

	virtual double perimeter() const override;
	virtual double area() const override;
	virtual void print() const override;
	virtual bool containsFigure(const Figure*) const override;
	virtual bool containsPoint(const Point&) const override;
	virtual Figure* clone() const override;
	virtual void translate(const double&, const double&) override;
};
