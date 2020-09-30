#pragma once

#include "Figure.hpp"

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);

    void print() const override;
    void zoom(int factor) override;
    bool is_inside(int x, int y) const override;

protected:
    int width_;
    int height_;
};
