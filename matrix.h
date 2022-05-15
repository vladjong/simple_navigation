#pragma once

#include <stdexcept>

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
    // Accessors
    int getRows() { return rows_; }
    int getCols() { return cols_; }
    // Operators
    Matrix operator=(const Matrix& other);
    double& operator()(int i, int j);

 private:
    inline void allocateMatrix(int rows, int cols);
    inline void destroyMatrix();
    inline void copyMatrix(double** other_matrix);
};

}  // namespace s21
