#define _USE_MATH_DEFINES
#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include "Helpers.h"

Circle::Circle() {
	this->shape = Shape::circle;
	this->fill = Colour::other;
	this->center;
	radius = 0;
}

Circle::Circle(const Point& center, const double& radius, const Colour& colour) {
	this->shape = Shape::circle;
	this->fill = colour;
	this->center = center;
	this->radius = radius;
}

double Circle::getRadius() const {
	return this->radius;
}

Point Circle::getCenter() const {
	return this->center;
}

double Circle::perimeter() const {
	return 2 * M_PI * radius;
}

double Circle::area() const {
	return M_PI * pow(radius, 2);
}

void Circle::print() const {
	std::cout << "circle ";
	center.print();
	std::cout << " " << radius << " ";
	std::cout << colourToString(this->fill);
	std::cout << std::endl;
}

bool Circle::containsFigure(const Figure* figure) const {
	if (figure->getShape() == Shape::circle) {
		const Circle* circle = dynamic_cast<const Circle*>(figure);
		if (this->radius >= this->center.distance(circle->center) + circle->radius) {
			return true;
		}
	}
	else if (figure->getShape() == Shape::rectangle) {
		const Rectangle* rectangle = dynamic_cast<const Rectangle*>(figure);
		if (this->containsPoint(rectangle->getPoint()) &&
			this->containsPoint(rectangle->getPoint().offset(rectangle->getWidth(), rectangle->getHeight()))) {
			return true;
		}
	}
	else if (figure->getShape() == Shape::line) {
		const Line* line = dynamic_cast<const Line*>(figure);
		if (this->containsPoint(line->getP1()) &&
			this->containsPoint(line->getP2())) {
			return true;
		}
	}
	return false;
}

bool Circle::containsPoint(const Point& point) const {
	double distanceToCenter = this->center.distance(point);
	if (distanceToCenter <= this->radius) {
		return true;
	}
	return false;
}

Figure* Circle::clone() const {
	return new Circle(*this);
}

void Circle::translate(const double& x, const double& y) {
	this->center.translate(x, y);
}