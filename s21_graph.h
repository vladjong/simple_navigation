#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "matrix.h"

namespace s21 {

class Graph {
 private:
    Matrix matrix_;
    int size_{0};

 public:
    Graph() {}
    ~Graph() {}
    void loadGraphFromFile(std::string filename);
    void exportGraphToDot(std::string filename);
    const int &getSize() { return size_; }
    const Matrix& getMatrix() { return matrix_; }
};

}  // namespace s21

#include "s21_graph.inl"
