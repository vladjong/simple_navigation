#include "ant.h"

namespace s21 {

void Ant::initTabu() {
    for (int i = 0; i < matrixGraph_.getRows(); i++) {
        tabu_.push_back(true);
    }
    tabu_[position_] = false;
}

const std::map<int, double> Ant::determAvalibleWays() {
    std::map<int, double> avalibleWays;
    for (int i = 0; i < matrixGraph_.getRows(); i++) {
        if (matrixGraph_(position_, i) != 0 && tabu_[i]) {
            avalibleWays.insert(std::make_pair(i, matrixGraph_(position_, i)));
        }
    }
    return avalibleWays;
}

double Ant::calculateProbability(std::map<int, double>& avalibleWays, int index) {
    double ita = pow(1 / avalibleWays[index], kBeta);
    double teta = pow(pheromones_(position_, index), kAlpha);
    double probability = 100 * ita * teta;
    double divisor = 0;
    for (auto it = avalibleWays.begin(); it != avalibleWays.end(); ++it) {
        divisor += pow(1 / it->second, kBeta) * pow(pheromones_(position_, it->first), kAlpha);
    }
    return probability / divisor;
}

const std::map<int, double> Ant::calculateProbabilityWays() {
    std::map<int, double> probabilities;
    std::map<int, double> avalibleWays = determAvalibleWays();
    double currentProbability = 0;
    for (auto it = avalibleWays.begin(); it != avalibleWays.end(); ++it) {
    }
    for (auto it = avalibleWays.begin(); it != avalibleWays.end(); ++it) {
        currentProbability += calculateProbability(avalibleWays, it->first);
        probabilities.insert(std::make_pair(it->first, currentProbability));
    }
    return probabilities;
}

const double randomChoose() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> choise(0, 99);
    return choise(engine);
}

void Ant::chooseWay(std::map<int, double>& probabilities) {
    if (probabilities.size() == 1) {
        position_ = probabilities.begin()->first;
    }
    double random = randomChoose();
    for (auto it = probabilities.begin(); it != probabilities.end(); ++it) {
        if (random <= it->second) {
            position_ = it->first;
            break;
        }
    }
}

void Ant::calculatePath(const std::vector<int>& path) {
    for (int i = 0; i < path.size() - 1; i++) {
        lmin_ += matrixGraph_(path[i], path[i + 1]);
    }
    lmin_ += matrixGraph_(path[path.size() - 1], path[0]);
    std::cout << "result: " << lmin_ << "\n";
}

void Ant::updatePheromones(const std::vector<int>& path) {
    double tempTeta = kQ / lmin_;
    for (int i = 1; i < path.size(); i++) {
        pheromones_(path[0], path[i]) *= (1 - kP);
        pheromones_(path[0], path[i]) += tempTeta;
    }
}

void Ant::runAlgorithm() {
    std::cout << "begin position " << position_ << "\n";
    path_.push_back(position_);
    initTabu();
    for (int i = 0; i < matrixGraph_.getRows() - 1; i++) {
        std::map<int, double> probabilities = calculateProbabilityWays();
        chooseWay(probabilities);
        std::cout << "POSITION " << position_ << "\n";
        tabu_[position_] = false;
        path_.push_back(position_);
    }
    calculatePath(path_);
    updatePheromones(path_);
    pheromones_.print();
    std::cout << "path: ";
    for (auto&i : path_) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

}  // namespace s21