#pragma once

#include <map>
#include <random>
#include <vector>

#include "matrix.h"

namespace s21 {

const double kAlpha = 1.0;
const double kBeta = 1.0;
const double kQ = 1.0;
const double kP = 0.5;

class Ant {
 private:
    double lmin_ {0};
    int position_{0};
    Matrix pheromones_;
    Matrix matrixGraph_;
    std::vector<bool> tabu_;
    std::vector<int> path_;

    void initTabu();
    void chooseWay(std::map<int, double>& probabilities);
    const std::map<int, double> calculateProbabilityWays();
    const std::map<int, double> determAvalibleWays();
    double calculateProbability(std::map<int, double>& avalibleWays, int index);
    void calculatePath(const std::vector<int>& path);
    void updatePheromones(const std::vector<int>& path);
    void clear();

 public:
    Ant(int position_, Matrix pheromones, Matrix matrixGraph)
        : position_(position_), pheromones_(pheromones), matrixGraph_(matrixGraph) {}
    ~Ant() {}

    Matrix getPheromones() { return pheromones_; }
    double getLmin() { return lmin_; }
    std::vector<int>& getPath() { return path_; }

    void runAlgorithm();
};

}  // namespace s21

#include "ant.inl"