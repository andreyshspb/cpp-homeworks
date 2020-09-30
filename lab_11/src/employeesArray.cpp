#include <iostream>
#include <fstream>
#include <cassert>

#include "employee.hpp"
#include "developer.hpp"
#include "salesManager.hpp"
#include "employeesArray.hpp"
#include "bin_manip.hpp"

EmployeesArray::EmployeesArray() {
    len_ = 0;
    capacity_ = 1;
    employees_ = new Employee*[capacity_];
}

EmployeesArray::~EmployeesArray() {
    for (int i = 0; i < len_; i++) {
        delete employees_[i];
    }
    delete[] employees_;
}

void EmployeesArray::rebuilding() {
    capacity_ *= 2;
    auto temp = new Employee*[capacity_];
    for (int i = 0; i < len_; i++) {
        temp[i] = employees_[i];
    }
    delete[] employees_;
    employees_ = temp;
}

void EmployeesArray::add(Employee *e) {
    employees_[len_++] = e;
    if (len_ == capacity_) {
        rebuilding();
    }
}

int EmployeesArray::total_salary() const {
    int salary = 0;
    for (int i = 0; i < len_; i++) {
        salary += employees_[i]->salary();
    }
    return salary;
}

std::ostream& operator<<(std::ostream &stream, const EmployeesArray &workers) {
    for (int i = 1; i <= workers.len_; i++) {
        stream << i << ". ";
        stream << *workers.employees_[i - 1];
    }
    stream << "== Total salary: " << workers.total_salary() << "\n\n";
    return stream;
}

std::ofstream& operator<<(std::ofstream &stream, const EmployeesArray &workers) {
    stream << write_le_int32(workers.len_);
    for (int i = 1; i <= workers.len_; i++) {
        stream << *workers.employees_[i - 1];
    }
    return stream;
}

std::ifstream& operator>>(std::ifstream &stream, EmployeesArray &workers) {
    int workers_count = 0;
    stream >> read_le_int32(workers_count);
    for (int i = 0; i < workers_count; i++) {
        int worker_type = 0;
        stream >> read_le_int32(worker_type);
        Employee *employee = nullptr;
        if (worker_type == developer_type) {
            employee = new Developer;
        } else if (worker_type == saleManager_type) {
            employee = new SalesManager;
        }
        assert(employee != nullptr);
        stream >> *employee;
        workers.add(employee);
    }
    return stream;
}
