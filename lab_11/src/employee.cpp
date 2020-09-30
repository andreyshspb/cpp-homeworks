#include "employee.hpp"

#include <string>


static const int MAX_SIZE_OF_NAME = 101;


Employee::Employee() {
    name_ = new char[MAX_SIZE_OF_NAME];
    base_salary_ = 0;
}

Employee::~Employee() {
    delete[] name_;
}
