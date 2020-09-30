#include "Figure.hpp"

Figure::Figure(int id, int x, int y) : id_(id), x_(x), y_(y) {}

Figure::~Figure() = default;

void Figure::move(int new_x, int new_y) {
    x_ = new_x;
    y_ = new_y;
}

int Figure::return_id() {
    return id_;
}

