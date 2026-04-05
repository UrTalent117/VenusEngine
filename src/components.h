#pragma once
#include "obj.h"

class Line : public Component {
private:
    int x1, y1, x2, y2, R, G, B;

public:
    Line(Graphics* g, int x1, int y1, int x2, int y2, int R, int G, int B) : Component(g), x1(x1), y1(y1), x2(x2), y2(y2), R(R), G(G), B(B) {}

    void draw() override {
        graphics->drawLine(x1, y1, x2, y2, R, G, B);
    }

    void erase() override {
        graphics->clear();
    }
};

class Circle : public Component {
private:
    int x, y, radius, R, G, B;

public:
    Circle(Graphics* g, int x, int y, int radius, int R, int G, int B) : Component(g), x(x), y(y), radius(radius), R(R), G(G), B(B) {}

    void draw() override {
        graphics->drawCircle(x, y, radius, R, G, B);
    }

    void erase() override {
        graphics->clear();
    }
};

