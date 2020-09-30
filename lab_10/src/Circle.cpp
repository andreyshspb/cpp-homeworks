#include <iostream>
#include <cstring>

#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y) {
    radius_ = radius;
    label_ = new char[std::strlen(label) + 1];
    std::strcpy(label_, label);
}

Circle::~Circle() {
    delete[] label_;
}

void Circle::print() const {
    std::cout << "Circle " << id_;
    std::cout << ": x = " << x_ << " y = " << y_;
    std::cout << " radius = " << radius_ << " label = " << label_ << std::endl;
}

void Circle::zoom(int factor) {
    radius_ = radius_ * factor;
}

bool Circle::is_inside(int x, int y) const {
    int dist = (x_ - x) * (x_ - x) + (y_ - y) * (y_ - y);
    return radius_ * radius_ >= dist;
}
