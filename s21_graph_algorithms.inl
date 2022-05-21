#include "s21_graph_algorithms.h"

namespace s21 {

const std::vector<int> GraphAlgorithms::breadthFirstSearch(Graph &graph, int startVertex) {
    queue<int> myQueue;
    std::vector<bool> used(graph.getSize(), false);
    std::vector<int> visited;
    Matrix matrixGraph = graph.getMatrix();
    myQueue.push(startVertex);
    used[startVertex] = true;
    while (!myQueue.empty()) {
        int value = myQueue.front();
        myQueue.pop();
        for (int i = 0; i < graph.getSize(); i++) {
            if (matrixGraph(value, i) != 0 && used[i] == false) {
                myQueue.push(i);
                used[i] = true;
            }
        }
        visited.push_back(value + 1);
    }
    return visited;
}

const std::vector<int> GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) {
    stack<int> myStack;
    std::vector<bool> used(graph.getSize(), false);
    std::vector<int> visited;
    Matrix matrixGraph = graph.getMatrix();
    myStack.push(startVertex);
    while (!myStack.empty()) {
        int value = myStack.top();
        myStack.pop();
        if (used[value] == true) {
            continue;
        }
        used[value] = true;
        for (int i = 0; i < graph.getSize(); i++) {
            if (matrixGraph(value, i) != 0 && used[i] == false) {
                myStack.push(i);
            }
        }
        visited.push_back(value + 1);
    }
    return visited;
}

const double GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
    queue<int> myQueue;
    std::vector<bool> used(graph.getSize(), false);
    std::vector<double> minRoad(graph.getSize(), std::numeric_limits<double>::infinity());
    Matrix matrixGraph = graph.getMatrix();
    minRoad[vertex1] = 0;
    myQueue.push(vertex1);
    while (!myQueue.empty()) {
        int value = myQueue.front();
        myQueue.pop();
        used[value] = true;
        for (int i = 0; i < graph.getSize(); i++) {
            double tempRoad = minRoad[value] + matrixGraph(value, i);
            if (matrixGraph(value, i) != 0 && used[i] == false && minRoad[i] > tempRoad) {
                minRoad[i] = tempRoad;
                myQueue.push(i);
            }
        }
    }
    return minRoad[vertex2];
}

const int GraphAlgorithms::randomChoose() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> posRand(0, graph_.getSize() - 1);
    return posRand(engine);
}

void GraphAlgorithms::initPheromones() {
    for (int i = 0; i < graph_.getSize(); i++) {
        for (int j = 0; j < graph_.getSize(); j++) {
            if (pheromones_(i, j) != 0) {
                pheromones_(i, j) = 3;
            }
        }
    }
}

// Clear memory!!!
void GraphAlgorithms::generateAnt() {
    for (int i = 0; i < graph_.getSize(); i++) {
        int position = randomChoose();
        ants_.push_back(new Ant(position, pheromones_, graph_.getMatrix()));
    }
}

void GraphAlgorithms::updatePheromones() {
    Matrix pheromonesTemp(pheromones_.getRows(), pheromones_.getRows());
    for (int i = 0; i < graph_.getSize(); i++) {
        ants_[i]->runAlgorithm();
        pheromonesTemp += ants_[i]->getPheromones();
    }
    pheromonesTemp *= 1.0 /graph_.getSize();
    pheromones_ = pheromonesTemp;
    pheromones_.print();
}

std::vector<int> GraphAlgorithms::findDistance(double pathTemp) {
    int index = 0;
    for (int i = 0; i < graph_.getSize(); i++) {
        if (pathTemp == ants_[i]->getLmin()) {
            index = i;
            break;
        }
    }
    return ants_[index]->getPath();
}

void GraphAlgorithms::updateTsmResult(TsmResult &result) {
    std::vector<double> path;
    for (int i = 0; i < graph_.getSize(); i++) {
        path.push_back(ants_[i]->getLmin());
    }
    auto minElement = std::min_element(path.begin(), path.end());
    if (*minElement < result.distance) {
        result.distance = *minElement;
        result.vertices = findDistance(*minElement);
    }
    std::cout << "DISTANCE: " << result.distance;
}

void GraphAlgorithms::clear() {
    for (int i = 0; i < graph_.getSize(); i++) {
        delete ants_[i];
    }
    ants_.clear();
}

const TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph) {
    graph_ = graph;
    pheromones_ = graph_.getMatrix();
    initPheromones();
    TsmResult result;
    for (int i = 0; i < 30; i++) {
        generateAnt();
        updatePheromones();
        updateTsmResult(result);
        clear();
    }
    return result;
}

}  // namespace s21
