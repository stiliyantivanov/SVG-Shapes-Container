#pragma once

class Point {
private:
	double x, y;
public:
	Point();
	Point(const double&, const double&);

	double getX() const;
	double getY() const;

	void translate(const double&, const double&);
	void print() const;

	double distance(const Point&) const;

	Point offset(const double&, const double&) const;
};