#pragma once
#include <vector>

// single tour
struct Tour {
    std::vector<int> vertices;
};

// two tours
struct TwoTours {
    Tour tour1;
    Tour tour2;
};

// total tour length
int calculateTourLength(const std::vector<int>& tour, const std::vector<std::vector<int>>& distanceMatrix);

// random choose of two distinct starting vertices
std::pair<int, int> chooseRandomStartingVertices(size_t numVertices);

std::pair<int, int> chooseRandomFurthestVertices (size_t numVertices, const std::vector<std::vector<int>>& distanceMatrix);

// initializing tours with selected starting vertices and removing them from available vertices
std::pair<Tour, Tour> initializeToursAndRemoveStartingVertices(const std::pair<int, int>& startingVertices, const std::vector<std::vector<int>>& distanceMatrix);

// greedy expansion for a single tour
void greedyExpansion(Tour& tour, const std::vector<std::vector<int>>& distanceMatrix, const std::vector<int>& availableVertices);

// greedy algorithm with random starting vertices
TwoTours greedyAlgorithmRandomStart(const std::vector<std::vector<int>>& distanceMatrix, int tourSize);
