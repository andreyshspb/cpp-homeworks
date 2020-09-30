#pragma once


#include <utility>
#include <vector>
#include <string>


class Matrix {
public:

    void load(const std::string &file_name);
    void print() const;
    void add(const Matrix &other);
    void mul(const Matrix &other);
    void elem(int row, int col) const;

private:
    int row_ = 0;
    int column_ = 0;
    std::vector<std::vector<int>> matrix_;
};


class MatrixException : std::exception {
public:

    explicit MatrixException(std::string message) : message_(std::move(message)) {}

    const char* what() const noexcept override { return message_.c_str(); }

private:
    std::string message_;
};

