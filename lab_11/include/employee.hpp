#pragma once

#include <cstdint>
#include <iosfwd>
#include <fstream>

enum employees_type {
    developer_type = 1,
    saleManager_type = 2
};

class Employee {
public:
    Employee();
    virtual ~Employee();

    virtual int salary() const = 0;
    virtual void print_data(std::ostream& stream) const = 0;
    virtual void read_data(std::istream& stream) = 0;
    virtual void save_data(std::ostream& stream) const = 0;
    virtual void load_data(std::istream& stream) = 0;

protected:
    char *name_;
    int32_t base_salary_;
};

inline std::ostream& operator<<(std::ostream& stream, const Employee& worker) {
    worker.print_data(stream);
    return stream;
}

inline std::istream& operator>>(std::istream& stream, Employee& worker) {
    worker.read_data(stream);
    return stream;
}

inline std::ofstream& operator<<(std::ofstream& stream, const Employee& worker) {
    worker.save_data(stream);
    return stream;
}

inline std::ifstream& operator>>(std::ifstream& stream, Employee& worker) {
    worker.load_data(stream);
    return stream;
}
