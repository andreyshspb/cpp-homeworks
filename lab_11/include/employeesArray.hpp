#pragma once

#include "employee.hpp"

#include <iosfwd>

class EmployeesArray {
public:
    EmployeesArray();
    ~EmployeesArray();

    void add(Employee *e);
    int total_salary() const;

    friend std::ostream& operator<<(std::ostream &stream, const EmployeesArray &workers);
    friend std::ofstream& operator<<(std::ofstream &stream, const EmployeesArray &workers);
    friend std::ifstream& operator>>(std::ifstream &stream, EmployeesArray &workers);

private:
    void rebuilding();

    Employee **employees_;
    int32_t len_;
    int32_t capacity_;
};
