#pragma once

#include "Figure.h"

class FigureContainer {
private:
	size_t count, capacity;
	Figure** items;
public:
	FigureContainer();
	FigureContainer(const FigureContainer&);
	FigureContainer& operator=(const FigureContainer&);
	~FigureContainer();

	bool load(const char*);
	bool save(const char*);
	size_t getCount() const;

	void addFigure(const Figure&);
	Figure* deleteFigure(const size_t&);
	void translateAll(const double&, const double&);
	Figure* translate(const size_t&, const double&, const double&);
	
	void print() const;
	void printPerimerters() const;
	void printAreas() const;
	void figuresWithin(const Figure&) const;
	void figuresPointIn(const Point&) const;
private:
	void copy(const FigureContainer&);
	void free();
	void resize();
	void clear();
};