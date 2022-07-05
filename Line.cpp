#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include "Helpers.h"

Line::Line() {
	this->shape = Shape::line;
	this->fill = Colour::other;
	this->p1;
	this->p2;
}

Line::Line(const Point& p1, const Point& p2, const Colour& colour) {
	this->shape = Shape::line;
	this->fill = colour;
	this->p1 = p1;
	this->p2 = p2;
}

Point Line::getP1() const {
	return this->p1;
}

Point Line::getP2() const {
	return this->p2;
}

double Line::perimeter() const {
	return this->p1.distance(p2);
}

double Line::area() const {
	return 0;
}

void Line::print() const {
	std::cout << "line ";
	p1.print();
	std::cout << " ";
	p2.print();
	std::cout << " " << colourToString(this->fill);
	std::cout << std::endl;
}

bool Line::containsFigure(const Figure* figure) const {
	if (figure->getShape() == Shape::line) {
		const Line* line = dynamic_cast<const Line*>(figure);
		if(this->containsPoint(line->getP1()) && this->containsPoint(line->getP2())) {
			return true;
		}
	}
	return false;
}

bool Line::containsPoint(const Point& point) const {
	double distanceToP1 = this->p1.distance(point);
	double distanceToP2 = this->p2.distance(point);
	double length = this->p1.distance(this->p2);
	if (abs(length - distanceToP1 - distanceToP2) < pow(10, -6)) {
		return true;
	}
	return false;
}

Figure* Line::clone() const {
	return new Line(*this);
}

void Line::translate(const double& x, const double& y) {
	this->p1.translate(x, y);
	this->p2.translate(x, y);
}