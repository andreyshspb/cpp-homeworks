#pragma once

#include "Figure.hpp"

class Circle : public Figure {
public:
    Circle(int id, int x, int y, int radius, const char *label);

    ~Circle() override;

    void print() const override;
    void zoom(int factor) override;
    bool is_inside(int x, int y) const override;

protected:
    int radius_;
    char *label_;
};