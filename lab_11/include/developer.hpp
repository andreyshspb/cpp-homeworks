#pragma once

#include <iosfwd>

#include "employee.hpp"

class Developer : public Employee {
public:
    Developer();

    int salary() const override;
    void print_data(std::ostream& stream) const override;
    void read_data(std::istream& stream) override;
    void save_data(std::ostream& stream) const override;
    void load_data(std::istream& stream) override;

private:
    bool has_bonus_ = false;
};
