#pragma once

#include <stdexcept>
#include <iostream>

namespace s21 {

class Matrix {
  private:
    int rows_, cols_;
    double** matrix_;

 public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    ~Matrix();

    int getRows() { return rows_; }
    int getCols() { return cols_; }
    Matrix operator=(const Matrix& other);
    double& operator()(int i, int j);
    void sum_matrix(const Matrix& other);
    void mul_number(const double num);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator*=(const double value);

    void print();

 private:
    inline void allocateMatrix(int rows, int cols);
    inline void destroyMatrix();
    inline void copyMatrix(double** other_matrix);
};

}  // namespace s21
