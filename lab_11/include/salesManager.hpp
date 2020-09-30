#pragma once

#include <cstdint>

#include "employee.hpp"

class SalesManager : public Employee {
public:
    SalesManager();

    int salary() const override;
    void print_data(std::ostream& stream) const override;
    void read_data(std::istream& stream) override;
    void save_data(std::ostream& stream) const override;
    void load_data(std::istream& stream) override;

private:
    int32_t sold_nm_;
    int32_t price_;
};
