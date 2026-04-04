#pragma once
#include "obj.h"

class Line : public Component {
private:
    int x1, y1, x2, y2;

public:
    Line(Graphics* g, int x1, int y1, int x2, int y2) : Component(g), x1(x1), y1(y1), x2(x2), y2(y2) {}

    void draw() override {
        graphics->drawLine(x1, y1, x2, y2);
    }

    void erase() override {
        graphics->clear();
    }
};

class Circle : public Component {
private:
    int x, y, radius;

public:
    Circle(Graphics* g, int x, int y, int radius) : Component(g), x(x), y(y), radius(radius) {}

    void draw() override {
        graphics->drawCircle(x, y, radius);
    }

    void erase() override {
        graphics->clear();
    }
};

