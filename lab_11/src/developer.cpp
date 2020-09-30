#include "employee.hpp"
#include "developer.hpp"
#include "bin_manip.hpp"

#include <iostream>
#include <fstream>

static char plus_or_minus(bool val) {
    if (val) { return '+'; }
    return '-';
}

Developer::Developer() : Employee() {
    has_bonus_ = false;
}

int Developer::salary() const {
    int salary = base_salary_;
    if (has_bonus_) { salary += 1000; }
    return salary;
}

void Developer::print_data(std::ostream& stream) const {
    stream << "Developer\n";
    stream << "Name: " << name_ << '\n';
    stream << "Base Salary: " << base_salary_ << '\n';
    stream << "Has bonus: " << plus_or_minus(has_bonus_) << '\n';
}

void Developer::read_data(std::istream &stream) {
    stream >> name_;
    stream >> base_salary_;
    stream >> has_bonus_;
}

void Developer::save_data(std::ostream& stream) const {
    stream << write_le_int32(developer_type);
    stream << write_c_str(name_);
    stream << write_le_int32(base_salary_);
    stream << write_bool(has_bonus_);
}

void Developer::load_data(std::istream& stream) {
    stream >> read_c_str(name_);
    stream >> read_le_int32(base_salary_);
    stream >> read_bool(has_bonus_);
}
