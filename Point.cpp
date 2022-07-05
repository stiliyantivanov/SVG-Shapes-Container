#include <iostream>
#include <cmath>
#include "Point.h"

Point::Point(): x(0),y(0) {}

Point::Point(const double& x, const double& y) : x(x), y(y) {}

double Point::getX() const {
	return this->x;
}

double Point::getY() const {
	return this->y;
}

void Point::translate(const double& x, const double& y) {
	this->x += x;
	this->y += y;
}

void Point::print() const {
	std::cout << x << " " << y;
}

double Point::distance(const Point& other) const {
	double distanceX = this->x - other.x;
	double distanceY = this->y - other.y;
	return sqrt(pow(distanceX, 2) + pow(distanceY, 2));
}

Point Point::offset(const double& x, const double& y) const {
	return { this->x + x, this->y + y };
}