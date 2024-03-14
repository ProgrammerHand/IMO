#include "distance_calculation.h"
#include <iostream>
#include <cmath>


int calculateRoundedDistance(const Point& p1, const Point& p2) {
    double distance = std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
    return static_cast<int>(std::round(distance));
}

std::vector<std::vector<int>> calculateDistanceMatrix(const std::vector<Point>& nodes) {
    std::vector<std::vector<int>> distanceMatrix(nodes.size(), std::vector<int>(nodes.size(), 0));
    for (size_t i = 0; i < nodes.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            int distance = calculateRoundedDistance(nodes[i], nodes[j]);
            distanceMatrix[i][j] = distance;
            distanceMatrix[j][i] = distance;  // symmetric matrix
        }
    }
    return distanceMatrix;
}

void printDistanceMatrix(const std::vector<std::vector<int>>& distanceMatrix) {
    std::cout << "Distance Matrix:\n";
    for (size_t i = 0; i < distanceMatrix.size(); ++i) {
        for (size_t j = 0; j < distanceMatrix[i].size(); ++j) {
            std::cout << distanceMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}