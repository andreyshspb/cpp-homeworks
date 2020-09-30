#include "employee.hpp"
#include "salesManager.hpp"
#include "bin_manip.hpp"

#include <iostream>

SalesManager::SalesManager() : Employee() {
    sold_nm_ = 0;
    price_ = 0;
}

int SalesManager::salary() const {
    return base_salary_ + (int)(sold_nm_ * price_ * 0.01);
}

void SalesManager::print_data(std::ostream& stream) const {
    stream << "Sales Manager\n";
    stream << "Name: " << name_ << '\n';
    stream << "Base Salary: " << base_salary_ << '\n';
    stream << "Sold items: " << sold_nm_ << '\n';
    stream << "Item price: " << price_ << '\n';
}

void SalesManager::read_data(std::istream &stream) {
    stream >> name_;
    stream >> base_salary_;
    stream >> sold_nm_;
    stream >> price_;
}

void SalesManager::save_data(std::ostream& stream) const {
    stream << write_le_int32(saleManager_type);
    stream << write_c_str(name_);
    stream << write_le_int32(base_salary_);
    stream << write_le_int32(sold_nm_);
    stream << write_le_int32(price_);
}

void SalesManager::load_data(std::istream& stream) {
    stream >> read_c_str(name_);
    stream >> read_le_int32(base_salary_);
    stream >> read_le_int32(sold_nm_);
    stream >> read_le_int32(price_);
}
