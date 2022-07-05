#include <iostream>
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include "Helpers.h"

Rectangle::Rectangle() {
	this->shape = Shape::rectangle;
	this->fill = Colour::other;
	this->point;
	this->width = 0;
	this->height = 0;
}

Rectangle::Rectangle(const Point& point, const double& width, const double& height, const Colour& colour) {
	this->shape = Shape::rectangle;
	this->fill = colour;
	this->point = point;
	this->width = width;
	this->height = height;
}

double Rectangle::getWidth() const {
	return this->width;
}

double Rectangle::getHeight() const {
	return this->height;
}

Point Rectangle::getPoint() const {
	return this->point;
}

double Rectangle::perimeter() const {
	return 2 * (width + height);
}

double Rectangle::area() const {
	return width * height;
}

void Rectangle::print() const {
	std::cout << "rectangle ";
	point.print();
	std::cout << " " << width << " " << height << " ";
	std::cout << colourToString(this->fill) << std::endl;
}

bool Rectangle::containsFigure(const Figure* figure) const {
	if (figure->getShape() == Shape::rectangle) {
		const Rectangle* rectangle = dynamic_cast<const Rectangle*>(figure);
		if (this->containsPoint(rectangle->getPoint()) &&
			this->containsPoint(rectangle->getPoint().offset(rectangle->getWidth(), rectangle->getHeight()))) {
			return true;
		}
	}
	else if (figure->getShape() == Shape::circle) {
		const Circle* circle = dynamic_cast<const Circle*>(figure);
		if (this->containsPoint(circle->getCenter()) &&
			this->containsPoint(circle->getCenter().offset(circle->getRadius(),0)) &&
			this->containsPoint(circle->getCenter().offset(-circle->getRadius(), 0)) &&
			this->containsPoint(circle->getCenter().offset(0, circle->getRadius())) &&
			this->containsPoint(circle->getCenter().offset(0, -circle->getRadius()))) {
			return true;
		}
	}
	else if (figure->getShape() == Shape::line) {
		const Line* line = dynamic_cast<const Line*>(figure);
		if (this->containsPoint(line->getP1()) && this->containsPoint(line->getP2())) {
			return true;
		}
	}
	return false;
}

bool isBetween(const double number, const double limit1, const double limit2) {
	if (limit1 >= limit2) {
		return (limit1 >= number && number >= limit2);
	}
	return (limit1 <= number && number <= limit2);
}

bool Rectangle::containsPoint(const Point& point) const {
	if (isBetween(point.getX(), this->point.getX(), this->point.getX() + width) &&
		isBetween(point.getY(), this->point.getY(), this->point.getY() + height)) {
		return true;
	}
	return false;
}

Figure* Rectangle::clone() const {
	return new Rectangle(*this);
}

void Rectangle::translate(const double& x, const double& y) {
	this->point.translate(x, y);
}