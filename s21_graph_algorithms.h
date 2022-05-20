#pragma once

#include <algorithm>
#include <limits>
#include <random>
#include <vector>

#include "ant.h"
#include "containers/s21_queue.h"
#include "containers/s21_stack.h"
#include "s21_graph.h"

namespace s21 {

struct TsmResult {
    std::vector<int> vertices;
    double distance{INFINITY};
};

class GraphAlgorithms {
 private:
    Graph graph_;
    Matrix pheromones_{graph_.getMatrix()};
    std::vector<Ant *> ants_;

    void initPheromones();
    const int randomChoose();
    void generateAnt();
    void updatePheromones();
    void updateTsmResult(TsmResult &result);
    std::vector<int> &findDistance(double pathTemp);

 public:
    GraphAlgorithms(Graph graph) : graph_(graph) {}
    ~GraphAlgorithms() {}

    const std::vector<int> &breadthFirstSearch(Graph &graph, int startVertex);
    const std::vector<int> &depthFirstSearch(Graph &graph, int startVertex);
    const double getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
    const struct TsmResults &solveTravelingSalesmanProblem(Graph &graph);
};

}  // namespace s21
