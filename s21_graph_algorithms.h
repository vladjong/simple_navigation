#pragma once

#include <vector>
#include <limits>

#include "containers/s21_queue.h"
#include "containers/s21_stack.h"
#include "s21_graph.h"

namespace s21 {

struct TsmResult {
    int *vertices;
    double distance;
};

class GraphAlgorithms {
 private:
    Graph graph_;

 public:
    const std::vector<int> &breadthFirstSearch(Graph &graph, int startVertex);
    const std::vector<int> &depthFirstSearch(Graph &graph, int startVertex);
    const double getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
    const struct TsmResults &solveTravelingSalesmanProblem(Graph &graph);
};

}  // namespace s21
