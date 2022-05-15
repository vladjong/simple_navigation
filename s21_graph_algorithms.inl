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

}  // namespace s21
