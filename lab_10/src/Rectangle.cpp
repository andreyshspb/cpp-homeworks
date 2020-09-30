#include "Rectangle.hpp"

#include <iostream>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y) {
    width_ = width;
    height_ = height;
}

void Rectangle::print() const {
    std::cout << "Rectangle " << id_;
    std::cout << ": x = " << x_ << " y = " << y_;
    std::cout << " width = " << width_ << " height = " << height_ << std::endl;
}

void Rectangle::zoom(int factor) {
    width_ = width_ * factor;
    height_ = height_ * factor;
}

bool Rectangle::is_inside(int x, int y) const {
    if (!(2 * x_ - width_ <= 2 * x && 2 * x <= 2 * x_ + width_)) {
        return false;
    }
    return 2 * y_ - height_ <= 2 * y && 2 * y <= 2 * y_ + height_;
}
