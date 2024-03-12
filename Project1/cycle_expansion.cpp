#include "cycle_expansion.h"
#include <random>
#include <chrono>
#include <iostream>
#include <limits> 

int RandomElement::get_random_node(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) {
        return static_cast<int>(-1); 
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);

    int numRows = matrix.size();

    std::uniform_int_distribution<int> rowDist(0, numRows - 1);
    int randomRowIndex = rowDist(gen);

    return randomRowIndex;
}

int RandomElement::find_closest_node(const std::vector<std::vector<int>>& distanceMatrix, int chosenRowIndex, std::vector<bool> isInGraph) {
    int numNodes = distanceMatrix[chosenRowIndex].size();
    int closestNodeIndex = 0;
    int minDistance = std::numeric_limits<int>::max();

    for (int i = 0; i < numNodes; ++i) {
        if (isInGraph[i] && distanceMatrix[chosenRowIndex][i] < minDistance) {
            minDistance = distanceMatrix[chosenRowIndex][i];
            closestNodeIndex = i;
        }
    }

    return closestNodeIndex;
}

int RandomElement::create_cycle(const std::vector<std::vector<int>>& distanceMatrix, int randomRowIndex, int closestNodeIndex, std::vector<bool> isInGraph) {
    int numNodes = distanceMatrix.size();
    std::cout << "num of nodes to find cost " << numNodes << '\n';
    int lowestCostNodeIndex = 0;
    int lowestCost = std::numeric_limits<int>::max();

    for (int i = 0; i < numNodes; i++) {
        if (i != randomRowIndex && i != closestNodeIndex && !isInGraph[i]) {
            int cycleCost = distanceMatrix[closestNodeIndex][i] + distanceMatrix[i][randomRowIndex];
            if (cycleCost < lowestCost) {
                lowestCost = cycleCost;
                lowestCostNodeIndex = i;
            }
        }
    }

    return lowestCostNodeIndex;
}

