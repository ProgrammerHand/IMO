#pragma once
#include <vector>

struct Result {
    std::vector<std::vector<int>> graph;
    std::vector<bool> isInGraph;
};

class GraphBuilder {
public:
    static Result buildGraph(const std::vector<std::vector<int>>& distanceMatrix, std::vector<bool> isInGraph, int numGraphRows);
};
