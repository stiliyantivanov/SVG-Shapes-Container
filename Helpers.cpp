#include <cstring>
#include "Helpers.h"

#pragma warning(disable: 4996)

Colour determineColour(const char* colourName) {
    if (strcmp(colourName, "white") == 0) {
        return Colour::white;
    }
    if (strcmp(colourName, "black") == 0) {
        return Colour::black;
    }
    if (strcmp(colourName, "red") == 0) {
        return Colour::red;
    }
    if (strcmp(colourName, "green") == 0) {
        return Colour::green;
    }
    if (strcmp(colourName, "blue") == 0) {
        return Colour::blue;
    }
    if (strcmp(colourName, "yellow") == 0) {
        return Colour::yellow;
    }
    if (strcmp(colourName, "orange") == 0) {
        return Colour::orange;
    }
    if (strcmp(colourName, "purple") == 0) {
        return Colour::purple;
    }
    return Colour::other;
}

const char* shapeToString(const Shape& shape) {
    switch (shape) {
    case rectangle: return "rectangle";
    case circle: return "circle";
    case line: return "line";
    }
    return nullptr;
}

const char* colourToString(const Colour& colour) {
    switch (colour) {
    case white: return "white";
    case black: return "black";
    case red: return "red";
    case green: return "green";
    case blue: return "blue";
    case yellow: return "yellow";
    case orange: return "orange";
    case purple: return "purple";
    }
    return nullptr;
}

// converts char array into int number
int convertToInt(const char* input) {
    int number = 0;
    bool isNegative = false;
    for (int i = 0; input[i] != '\0'; i++) {
        // checks whether the number is negative
        if (i == 0 && input[i] == '-') {
            isNegative = true;
            continue;
        }
        number += input[i] - '0';
        number *= 10;
    }
    number /= 10;

    if (isNegative) {
        number = -number;
    }
    return number;
}

// converts char array into double number
double convertToDouble(const char* input) {
    double number = 0.0;
    bool isNegative = false, hasDecimalPoint = false;
    int numberDigitsAfterDecimalPoint = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        // checks whether the number is negative
        if (i == 0 && input[i] == '-') {
            isNegative = true;
            continue;
        }
        // checks whether the number has a decimal point
        if ((input[i] == '.' || input[i] == ',') && hasDecimalPoint == false) {
            hasDecimalPoint = true;
            continue;
        }
        else {
            // counts the number of digits after the decimal point
            if (hasDecimalPoint == true) {
                numberDigitsAfterDecimalPoint++;
            }
            number += input[i] - '0';
            number *= 10;
        }
    }
    for (int j = 0; j <= numberDigitsAfterDecimalPoint; j++) {
        number /= 10;
    }

    if (isNegative) {
        number = -number;
    }
    return number;
}