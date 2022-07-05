#include <iostream>
#include <fstream>
#include "FigureContainer.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "Helpers.h"
#include "Parse.h"

void FigureContainer::copy(const FigureContainer& other) {
	this->count = other.count;
	this->capacity = other.capacity;
	this->items = new Figure * [this->capacity];
	for (size_t i = 0; i < count; i++) {
		if (other.items[i] != nullptr) {
			this->items[i] = other.items[i]->clone();
		}
		this->items[i] = nullptr;
	}
}

void FigureContainer::free() {
	for (size_t i = 0; i < count; i++) {
		delete this->items[i];
	}
	delete[] items;
}

void FigureContainer::resize() {
	Figure** temp = new Figure * [capacity *= 2];
	for (size_t i = 0; i < count; i++) {
		temp[i] = items[i];
	}
	delete[] items;
	items = temp;
	temp = nullptr;
}

void FigureContainer::clear() {
	free();
	this->count = 0;
	this->capacity = 2;
	this->items = new Figure * [capacity];
}

FigureContainer::FigureContainer() {
	count = 0;
	capacity = 2;
	this->items = new Figure * [capacity];
}

FigureContainer::FigureContainer(const FigureContainer& other) {
	copy(other);
}

FigureContainer& FigureContainer::operator=(const FigureContainer& other) {
	if (this != &other) {
		free();
		copy(other);
	}
	return *this;
}

FigureContainer::~FigureContainer() {
	free();
}

bool FigureContainer::load(const char* filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		return false;
	}
	char* input = new char[1024];
	do {
		file.getline(input, 1024);
	} 
	while (strcmp(input, "<svg>") != 0);
	file.getline(input, 1024);
	while (strcmp(input, "</svg>") != 0) {
		char** result = parseLine(input);
		if (strcmp(result[0], "rect") == 0) {
			double x = convertToDouble(result[1]);
			double y = convertToDouble(result[2]);
			double width = convertToDouble(result[3]);
			double height = convertToDouble(result[4]);
			Colour fill = determineColour(result[5]);
			Rectangle rectangle({ x,y }, width, height, fill);
			this->addFigure(rectangle);
		}
		else if (strcmp(result[0], "circle") == 0) {
			double x = convertToDouble(result[1]);
			double y = convertToDouble(result[2]);
			double radius = convertToDouble(result[3]);
			Colour fill = determineColour(result[4]);
			Circle circle({ x,y }, radius, fill);
			this->addFigure(circle);
		}
		else if (strcmp(result[0], "line") == 0) {
			double x1 = convertToDouble(result[1]);
			double y1 = convertToDouble(result[2]);
			double x2 = convertToDouble(result[3]);
			double y2 = convertToDouble(result[4]);
			Colour fill = determineColour(result[5]);
			Line line({ x1,y1 }, {x2,y2}, fill);
			this->addFigure(line);
		}

		for (size_t j = 0; j < 6; j++)
			delete[] result[j];
		delete[] result;
		
		file.getline(input, 1024);
	}

	delete[] input;
	return true;
}

bool FigureContainer::save(const char* filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		return false;
	}
	file << "<!DOCTYPE html>" << std::endl;
	file << "<html>" << std::endl;
	file << "<body>" << std::endl;
	file << "<svg>" << std::endl;

	for (size_t i = 0; i < this->count; i++) {
		if (this->items[i] != nullptr) {
			switch (this->items[i]->getShape()) {
				case rectangle: {
					Rectangle* rectangle = dynamic_cast<Rectangle*>(this->items[i]);
					file << "<rect x = \"" << rectangle->getPoint().getX() << "\" y=\"" << rectangle->getPoint().getY();
					file << "\" width=\"" << rectangle->getWidth() << "\" heigth=\"" << rectangle->getHeight();
					file << "\" fill=\"" << colourToString(rectangle->getFill()) << "\"/>" << std::endl;
					break;
				}
				case circle: {
					Circle* circle = dynamic_cast<Circle*>(this->items[i]);
					file << "<circle cx=\"";
					file << circle->getCenter().getX() << "\" cy=\"" << circle->getCenter().getY();
					file << "\" radius=\"" << circle->getRadius();
					file << "\" fill=\"" << colourToString(circle->getFill()) << "\"/>" << std::endl;
					break;
				}
				case line: {
					file << "<line ";
					Line* line = dynamic_cast<Line*>(this->items[i]);
					file << "x1 = \"" << line->getP1().getX() << "\" y1=\"" << line->getP1().getY() << "\" ";
					file << "x2 = \"" << line->getP2().getX() << "\" y2=\"" << line->getP2().getY();
					file << "\" fill=\"" << colourToString(line->getFill()) << "\"/>" << std::endl;
					break;
				}
			}
		}
	}

	file << "</svg>" << std::endl;
	file << "</body>" << std::endl;
	file << "</html>" << std::endl;
	file.close();

	this->clear();

	return true;
}

size_t FigureContainer::getCount() const {
	return this->count;
}

void FigureContainer::addFigure(const Figure& figure) {
	if (count >= capacity) {
		resize();
	}
	this->items[count++] = figure.clone();
}

Figure* FigureContainer::deleteFigure(const size_t& index) {
	if (count > index) {
		if (this->items[index] != nullptr) {
			Figure* figure = this->items[index];
			this->items[index] = nullptr;
			return figure;
		}
	}
	return nullptr;
}

void FigureContainer::translateAll(const double& x, const double& y) {
	for (size_t i = 0; i < count; i++) {
		if (this->items[i] != nullptr) {
			this->items[i]->translate(x, y);
		}
	}
}

Figure* FigureContainer::translate(const size_t& index, const double& x, const double& y) {
	if (count > index) {
		if (this->items[index] != nullptr) {
			this->items[index]->translate(x, y);
			return this->items[index];
		}
	}
	return nullptr;
}

void FigureContainer::print() const {
	for (size_t i = 0; i < count; i++) {
		if (this->items[i] != nullptr) {
			std::cout << i + 1 << ". ";
			this->items[i]->print();
		}
	}
}

void FigureContainer::printPerimerters() const {
	for (size_t i = 0; i < count; i++) {
		if (this->items[i] != nullptr) {
			std::cout << i + 1 << ". " << this->items[i]->perimeter() << std::endl;
		}
	}
}

void FigureContainer::printAreas() const {
	for (size_t i = 0; i < count; i++) {
		if (this->items[i] != nullptr) {
			std::cout << i + 1 << ". " << this->items[i]->area() << std::endl;
		}
	}
}

void FigureContainer::figuresWithin(const Figure& figure) const {
	bool noFigures = true;
	for (size_t i = 0; i < count; i++) {
		if (this->items[i] != nullptr) {
			if (figure.containsFigure(this->items[i])) {
				std::cout << i + 1 << ". ";
				this->items[i]->print();
				noFigures = false;
			}
		}
	}
	if (noFigures) {
		std::cout << "No figures are located within ";
		figure.print();
	}
}

void FigureContainer::figuresPointIn(const Point& point) const {
	bool noFigures = true;
	for (size_t i = 0; i < count; i++) {
		if (this->items[i] != nullptr) {
			if (this->items[i]->containsPoint(point)) {
				std::cout << i + 1 << ". ";
				this->items[i]->print();
				noFigures = false;
			}
		}
	}
	if (noFigures) {
		std::cout << "No figures contain the point ";
		point.print();
		std::cout << std::endl;
	}
}