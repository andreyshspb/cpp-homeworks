#include "matrix.hpp"

#include <fstream>
#include <vector>
#include <iostream>


void Matrix::load(const std::string &file_name) {
    std::ifstream file(file_name);
    if (!file) throw MatrixException("LOAD: unable to open file.");
    int row, column;
    if (!(file >> row)) throw MatrixException("LOAD: invalid file format.");
    if (!(file >> column)) throw MatrixException("LOAD: invalid file format.");
    std::vector<std::vector<int>> matrix(row, std::vector<int>(column));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (!(file >> matrix[i][j])) throw MatrixException("LOAD: invalid file format.");
        }
    }
    row_ = row;
    column_ = column;
    matrix_ = matrix;
}


void Matrix::print() const {
    for (int i = 0; i < row_; i++) {
        for (int j = 0; j < column_; j++) {
            std::cout << matrix_[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}


void Matrix::add(const Matrix &other) {
    if (row_ != other.row_ || column_ != other.column_) {
        throw MatrixException("ADD: dimensions do not match.");
    }
    for (int i = 0; i < row_; i++) {
        for (int j = 0; j < column_; j++) {
            matrix_[i][j] += other.matrix_[i][j];
        }
    }
}


void Matrix::mul(const Matrix &other) {
    if (column_ != other.row_) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
    std::vector<std::vector<int>> temp_matrix(row_, std::vector<int>(other.column_));
    for (int i = 0; i < row_; i++) {
        for (int j = 0; j < other.column_; j++) {
            for (int k = 0; k < column_; k++) {
                temp_matrix[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    column_ = other.column_;
    matrix_ = temp_matrix;
}


void Matrix::elem(int row, int col) const {
    if (row < 0 || row >= row_ || col < 0 || col >= column_) {
        throw MatrixException("ACCESS: bad index.");
    }
    std::cout << matrix_[row][col] << std::endl;
}



