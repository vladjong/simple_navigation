#include "ant.h"

namespace s21 {

void Ant::initTabu() {
    for (int i = 0; i < matrixGraph_.getRows(); i++) {
        tabu_.push_back(false);
    }
    tabu_[position_] = true;
}

const std::map<int, double>& Ant::determAvalibleWays() {
    std::map<int, double> avalibleWays;
    for (int i = 0; i < matrixGraph_.getRows(); i++) {
        if (matrixGraph_(position_, i) != 0) {
            avalibleWays.insert(std::make_pair(i, matrixGraph_(position_, i)));
        }
    }
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

const std::map<int, double>& Ant::calculateProbabilityWays() {
    std::map<int, double> probabilities;
    std::map<int, double> avalibleWays = determAvalibleWays();
    double currentProbability = 0;
    for (auto it = avalibleWays.begin(); it != avalibleWays.end(); ++it) {
        currentProbability += calculateProbability(avalibleWays, it->first);
        probabilities.insert(std::make_pair(it->first, currentProbability));
    }
    return probabilities;
}

const double randomChoose() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> choise(0, 100);
    return choise(engine);
}

void Ant::chooseWay(std::map<int, double>& probabilities) {
    double random = randomChoose();
    for (auto it = probabilities.begin(); it != probabilities.end(); ++it) {
        if (random < it->second) {
            position_ = it->first;
        }
    }
}

void Ant::calculatePath(const std::vector<int>& path) {
    for (int i = 0; i < path.size(); i++) {
        if (i != path.size() - 1) {
            lmin_ += matrixGraph_(path[i], path[i + 1]);
        } else {
            lmin_ += matrixGraph_(path[i], path[0]);
        }
    }
}

void Ant::updatePheromones(const std::vector<int>& path) {
    double tempTeta = kQ /lmin_;
    for (int i = 1; i < path.size(); i++) {
        pheromones_(path[0], path[i]) *= (1 - kP);
        pheromones_(path[0], path[i]) += tempTeta;
    }
}

void Ant::runAlgorithm() {
    path_.push_back(position_);
    initTabu();
    for (int i = 0; i < matrixGraph_.getRows(); i++) {
        std::map<int, double> probabilities = calculateProbabilityWays();
        chooseWay(probabilities);
        tabu_[position_] = true;
        path_.push_back(position_);
    }
    calculatePath(path_);
    updatePheromones(path_);
}

}  // namespace s21