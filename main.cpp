#include <iostream>
#include "FigureContainer.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include "Helpers.h"
#include "Parse.h"

int main()
{
    FigureContainer container;

    char filename[MAX_LENGTH_INPUT];
    bool invalidFilename = false;
    do {
        std::cout << "> open ";
        std::cin >> filename;
        if (!container.load(filename)) {
            std::cout << "There is no file with such a name!" << std::endl;
            invalidFilename = true;
        }
    } while (invalidFilename);

    bool opened = true;
    bool run = true;

    char command[MAX_LENGTH_INPUT];

    while (run) {
        while (opened) {
            std::cout << "> ";
            std::cin >> command;

            if (strcmp(command, "print") == 0) {
                container.print();
            }
            else if (strcmp(command, "pers") == 0) {
                container.printPerimerters();
            }
            else if (strcmp(command, "areas") == 0) {
                container.printAreas();
            }
            else if (strcmp(command, "create") == 0) {
                char type[MAX_LENGTH_INPUT];
                std::cin >> type;
                if (strcmp(type, "rectangle") == 0) {
                    double x, y, width, height;
                    char colour[MAX_LENGTH_INPUT];
                    std::cin >> x >> y >> width >> height >> colour;
                    Point point(x, y);
                    Rectangle rectangle(point, width, height, determineColour(colour));
                    container.addFigure(rectangle);
                    std::cout << "Successfully created rectangle (" << container.getCount() << ")" << std::endl;
                }
                else if (strcmp(type, "circle") == 0) {
                    double x, y, radius;
                    char colour[MAX_LENGTH_INPUT];
                    std::cin >> x >> y >> radius >> colour;
                    Point point(x, y);
                    Circle circle(point, radius, determineColour(colour));
                    container.addFigure(circle);
                    std::cout << "Successfully created circle (" << container.getCount() << ")" << std::endl;
                }
                else if (strcmp(type, "line") == 0) {
                    double x1, y1, x2, y2;
                    char colour[MAX_LENGTH_INPUT];
                    std::cin >> x1 >> y1 >> x2 >> y2 >> colour;
                    Point point1(x1, y1), point2(x2, y2);
                    Line line(point1, point2, determineColour(colour));
                    container.addFigure(line);
                    std::cout << "Successfully created line (" << container.getCount() << ")" << std::endl;
                }
            }
            else if (strcmp(command, "erase") == 0) {
                size_t index;
                std::cin >> index;
                Figure* figure = container.deleteFigure(index - 1);
                if (figure != nullptr) {
                    std::cout << "Erased a " << shapeToString(figure->getShape()) << "(" << index << ")" << std::endl;
                    delete figure;
                }
                else {
                    std::cout << "There is no figure number " << index << "!" << std::endl;
                }
            }
            else if (strcmp(command, "translate") == 0) {
                char input[MAX_LENGTH_INPUT];
                std::cin.getline(input, MAX_LENGTH_INPUT,'\n');
                char** parameters = parseTranslateParameters(input);
                if (parameters[2] == nullptr) {
                    container.translateAll(convertToDouble(parameters[0]), convertToDouble(parameters[1]));
                    std::cout << "Translated all figures" << std::endl;
                }
                else {
                    size_t index = convertToInt(parameters[0]);
                    double x = convertToDouble(parameters[1]);
                    double y = convertToDouble(parameters[2]);
                    Figure* figure = container.translate(index - 1, x, y);
                    if (figure != nullptr) {
                        std::cout << "Translated a " << shapeToString(figure->getShape()) << "(" << index << ")" << std::endl;
                    }
                    else {
                        std::cout << "There is no figure number " << index << "!" << std::endl;
                    }
                }
            }
            else if (strcmp(command, "within") == 0) {
                char type[MAX_LENGTH_INPUT];
                std::cin >> type;
                if (strcmp(type, "rectangle") == 0) {
                    double x, y, width, height;
                    char colour[MAX_LENGTH_INPUT];
                    std::cin >> x >> y >> width >> height >> colour;
                    Point point(x, y);
                    Rectangle rectangle(point, width, height, determineColour(colour));
                    container.figuresWithin(rectangle);
                }
                else if (strcmp(type, "circle") == 0) {
                    double x, y, radius;
                    char colour[MAX_LENGTH_INPUT];
                    std::cin >> x >> y >> radius >> colour;
                    Point point(x, y);
                    Circle circle(point, radius, determineColour(colour));
                    container.figuresWithin(circle);
                }
                else if (strcmp(type, "line") == 0) {
                    double x1, y1, x2, y2;
                    char colour[MAX_LENGTH_INPUT];
                    std::cin >> x1 >> y1 >> x2 >> y2 >> colour;
                    Point point1(x1, y1), point2(x2, y2);
                    Line line(point1, point2, determineColour(colour));
                    container.figuresWithin(line);
                }
            }
            else if (strcmp(command, "point") == 0) {
                double x, y;
                std::cin >> x >> y;
                Point point(x, y);
                container.figuresPointIn(point);
            }
            else if (strcmp(command, "save") == 0) {
                container.save(filename);
                std::cout << "Successfully saved the changes to " << filename << std::endl;
                opened = false;
                continue;
            }
            else if (strcmp(command, "exit") == 0) {
                std::cout << "Exit" << std::endl;
                run = false;
                return 0;
            }
            else {
                std::cout << "Invalid command!" << std::endl;
            }
        }
        if (!opened) {
            std::cout << "> ";
            std::cin >> command;
            if (strcmp(command, "open") == 0) {
                std::cin >> filename;
                if (!container.load(filename)) {
                    std::cout << "There is no file with such a name!" << std::endl;
                }
                else {
                    opened = true;
                    continue;
                }
            }
            else if (strcmp(command, "exit") == 0) {
                std::cout << "Exit" << std::endl;
                run = false;
                return 0;
            }
            else {
                std::cout << "Invalid command!" << std::endl;
            }
        }
    }

    return 0;
}