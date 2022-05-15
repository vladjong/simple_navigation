#include "s21_graph.h"

namespace s21 {

void Graph::loadGraphFromFile(std::string filename) {
    std::ifstream file = std::ifstream(filename);
    file >> size_;
    matrix_ = Matrix(size_, size_);
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            file >> matrix_(i, j); 
        }
    }
}

void Graph::exportGraphToDot(std::string filename) {
    std::ofstream output(filename);
    output << size_ << std::endl;
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            output << matrix_(i, j) << " ";
        }
        output << std::endl;
    }
}

}  // namespace s21