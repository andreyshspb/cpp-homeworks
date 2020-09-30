#include "bin_manip.hpp"

#include <iostream>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;

// ================== CONST =================

static const int MAX_SIZE_OF_C_STRING = 101;

// ================== INT ==================

std::ostream& write_le_int32::operator()(std::ostream &out) const {
    out.write((char *) (&data_), sizeof(int));
    return out;
}


std::ostream &operator <<(std::ostream &out, write_le_int32 const &data) {
    return data(out);
}


read_le_int32::read_le_int32(int &data) {
    data_ = &data;
}


std::istream& read_le_int32::operator()(std::istream &in) {
    in.read((char *) (data_), sizeof(int));
    return in;
}


std::istream &operator >>(std::istream &in, read_le_int32 data) {
    return data(in);
}

// ================== BOOL ==================

std::ostream& write_bool::operator()(std::ostream &out) const {
    return out << static_cast<char>(data_);
}


std::ostream &operator <<(std::ostream &out, write_bool const &data) {
    return data(out);
}


read_bool::read_bool(bool &data) {
    data_ = &data;
}


std::istream& read_bool::operator()(std::istream &in) {
    char buffer;
    in >> buffer;
    *data_ = (buffer == 1);
    return in;
}


std::istream &operator >>(std::istream &in, read_bool data) {
    return data(in);
}

// ================== C-STRING ==================


std::ostream& write_c_str::operator()(std::ostream &out) const {
    out << data_ << '\0';
    return out;
}


std::ostream &operator <<(std::ostream &out, write_c_str const &data) {
    return data(out);
}


std::istream& read_c_str::operator()(std::istream &in) {
    char buffer;
    in >> buffer;
    int i = 0;
    while (buffer != '\0') {
        data_[i++] = buffer;
        in >> buffer;
        assert(i < MAX_SIZE_OF_C_STRING);
    }
    data_[i] = buffer;

    return in;
}


std::istream &operator >>(std::istream &in, read_c_str data) {
    return data(in);
}
