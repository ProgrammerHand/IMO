#include <iostream>
#include <vector>
#include "file_management.h"
#include "distance_calculation.h"
#include "cycle_expansion.h"

int main() {
    const char* file_path = "kroB100.tsp";
    
    // read node coordinates and calculate distances
    std::vector<Point> nodes = readNodeCoordinates(file_path);

    // create matrix of distances
    std::vector<std::vector<int>> distanceMatrix = calculateDistanceMatrix(nodes);

    //Example distance matrix
    /*std::vector<std::vector<int>> distanceMatrix = {
        {0, 3, 5, 6, 9, 1},
        {3, 0, 2, 7, 1, 2},
        {5, 2, 0, 4, 8, 3},
        {6, 7, 4, 0, 10, 4},
        {9, 1, 8, 10, 0, 5}, 
        {1, 2, 3, 4, 5, 0}
    };*/

    cycleExpansionAlgorithm(distanceMatrix);

    return 0;
}
