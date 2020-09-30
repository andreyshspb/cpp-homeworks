#include "Scheme.hpp"

#include <cassert>

Scheme::Scheme(int capacity) {
    figures_ = new Figure*[capacity];
    capacity_ = capacity;
    size_ = 0;
    for (int i = 0; i < capacity; i++) {
        figures_[i] = nullptr;
    }
}

Scheme::~Scheme() {
    for (int i = 0; i < capacity_; i++) {
        delete figures_[i];
    }
    delete[] figures_;
}

int Scheme::get_index(int id) {
    for (int i = 0; i < size_; i++) {
        if (figures_[i]->return_id() == id) {
            return i;
        }
    }
    return -1;
}

void Scheme::push_back_figure(Figure *fg) {
    figures_[size_++] = fg;
}

void Scheme::remove_figure(int id) {
    int index = get_index(id);
    assert(index != -1);

    delete figures_[index];
    size_--;
    for (int i = index; i < size_; i++) {
        figures_[i] = figures_[i + 1];
    }
    figures_[size_] = nullptr;
}

void Scheme::print_all_figures() {
    for (int i = 0; i < size_; i++) {
        figures_[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor) {
    int index = get_index(id);
    assert(index != -1);

    figures_[index]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
    for (int i = 0; i < size_; i++) {
        if (figures_[i]->is_inside(x, y)) {
            return figures_[i];
        }
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    int index = get_index(id);
    assert(index != -1);

    figures_[index]->move(new_x, new_y);
}

