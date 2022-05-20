#include "matrix.h"

namespace s21 {

Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int cols) { allocateMatrix(rows, cols); }

Matrix::Matrix(const Matrix& other) : Matrix(other.rows_, other.cols_) { copyMatrix(other.matrix_); }

Matrix::~Matrix() { destroyMatrix(); }

Matrix Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        destroyMatrix();
        allocateMatrix(other.rows_, other.cols_);
        copyMatrix(other.matrix_);
    }
    return *this;
}

double& Matrix::operator()(int i, int j) { return matrix_[i][j]; }

inline void Matrix::allocateMatrix(int rows, int cols) {
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix_[i] = new double[cols]();
    }
}

inline void Matrix::destroyMatrix() {
    if (matrix_) {
        for (int i = 0; i < rows_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
    }
}

inline void Matrix::copyMatrix(double** other_matrix) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = other_matrix[i][j];
        }
    }
}

void Matrix::sum_matrix(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
        }
    }
}

void Matrix::mul_number(const double num) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] *= num;
        }
    }
}

Matrix& Matrix::operator+=(const Matrix& other) {
    sum_matrix(other);
    return *this;
}

Matrix& Matrix::operator*=(const double value) {
    mul_number(value);
    return *this;
}


}  // namespace s21
