#include <vector>
#include <iostream>
#include <limits>

#include "s21_graph.h"
#include "s21_graph_algorithms.h"
#include "ant.h"

int main() {
    s21::Graph graph;
    graph.loadGraphFromFile("/opt/goinfre/adough/simple_navigator/1.txt");
    s21::GraphAlgorithms al;
    al.solveTravelingSalesmanProblem(graph);
}