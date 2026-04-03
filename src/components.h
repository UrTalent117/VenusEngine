#pragma once
#include "obj.h"
#include <iostream>

class SetLine : public Component {
private:
    int x1, y1, x2, y2;

public:
    SetLine(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

    void draw() override {
        std::cout << "Drawing line from (" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ")" << std::endl;
    }

    void erase() override {
        std::cout << "Erasing line from (" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ")" << std::endl;
    }
};

class Circle : public Component {
private:
    int x, y, radius;

public:
    Circle(int x, int y, int radius) : x(x), y(y), radius(radius) {}

    void draw() override {
        std::cout << "Drawing circle at (" << x << "," << y << ") with radius " << radius << std::endl;
    }

    void erase() override {
        std::cout << "Erasing circle at (" << x << "," << y << ") with radius " << radius << std::endl;
    }
};
