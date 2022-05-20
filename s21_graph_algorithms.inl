#include "s21_graph_algorithms.h"

namespace s21 {

const std::vector<int> &GraphAlgorithms::breadthFirstSearch(Graph &graph, int startVertex) {
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

const std::vector<int> &GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) {
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
    std::uniform_int_distribution<int> posRand(0, graph_.getSize());
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
    for (int i = 0; i < graph_.getSize(); i++) {
        pheromones_ += ants_[i]->getPheromones();
    }
    pheromones_ *= 1 / graph_.getSize();
}

std::vector<int> &GraphAlgorithms::findDistance(double pathTemp) {
    for (int i = 0; i < graph_.getSize(); i++) {
        if (pathTemp == ants_[i]->getLmin()) {
            return ants_[i]->getPath();
        }
    }
}

void GraphAlgorithms::updateTsmResult(TsmResult &result) {
    std::vector<double> path;
    for (int i = 0; i < graph_.getSize(); i++) {
        path.push_back(ants_[i]->getLmin());
    }
    std::vector<double>::iterator result = std::min_element(path.begin(), path.end());
    double pathTemp = std::distance(path.begin(), result);
    if (pathTemp < result.distance) {
        result.distance = pathTemp;
        result.vertices = findDistance(pathTemp);
    }
}

const struct TsmResults &GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph) {
    initPheromones();
    int iteration = 0;
    TsmResult result;
    while (iteration < 10) {
        generateAnt();
        updatePheromones();
        updateTsmResult(result);
    }
    return result;
}

}  // namespace s21
