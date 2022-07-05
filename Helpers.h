#pragma once

#include "Figure.h"

const int MAX_LENGTH_INPUT = 100;

Colour determineColour(const char*);

const char* shapeToString(const Shape&);

const char* colourToString(const Colour&);

int convertToInt(const char*);

double convertToDouble(const char*);