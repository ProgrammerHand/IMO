#include <vector>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <random>
#include <chrono>
#include "greedy_expansion_knn.h"

// total tour length
int calculateTourLength(const std::vector<int>& tour, const std::vector<std::vector<int>>& distanceMatrix) {
    int length = 0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        length += distanceMatrix[tour[i]][tour[i + 1]];
    }
    length += distanceMatrix[tour.back()][tour.front()];  // return to the starting vertex
    return length;
}

// random choose of two distinct starting vertices
std::pair<int, int> chooseRandomStartingVertices(size_t numVertices) {
    srand(static_cast<unsigned>(time(0)));

    int startVertex1 = rand() % numVertices;
    int startVertex2;
    do {
        startVertex2 = rand() % numVertices;
    } while (startVertex2 == startVertex1);

    return {startVertex1, startVertex2};
}

std::pair<int, int> chooseRandomFurthestVertices (size_t numVertices, const std::vector<std::vector<int>>& distanceMatrix) {
    // srand(static_cast<unsigned>(time(0)));
    // int startVertex1 = rand() % numVertices;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> rowDist(0, numVertices - 1);
    int startVertex1 = rowDist(gen);
    
    // distances from startVertex1 to all other vertices
    std::vector<int> distances(numVertices);
    for (size_t i = 0; i < numVertices; ++i) {
        distances[i] = distanceMatrix[startVertex1][i];
    }

    // vertex with maximum distance as startVertex2
    int maxDistance = -1;
    int startVertex2 = -1;
    for (size_t i = 0; i < numVertices; ++i) {
        if (static_cast<int>(i) != startVertex1 && distances[i] > maxDistance) {
            maxDistance = distances[i];
            startVertex2 = static_cast<int>(i);
        }
    }
    std::cout << startVertex1 << "  " <<startVertex2 << std::endl;
    return {startVertex1, startVertex2};
}

// initializing tours with selected starting vertices and removing them from available vertices
std::pair<Tour, Tour> initializeToursAndRemoveStartingVertices(const std::pair<int, int>& startingVertices, const std::vector<std::vector<int>>& distanceMatrix) {
    Tour tour1 = {{startingVertices.first}};
    Tour tour2 = {{startingVertices.second}};

    std::vector<int> availableVertices(distanceMatrix.size());
    for (size_t i = 0; i < distanceMatrix.size(); ++i) {
        availableVertices[i] = i;
    }
    availableVertices.erase(std::remove(availableVertices.begin(), availableVertices.end(), startingVertices.first), availableVertices.end());
    availableVertices.erase(std::remove(availableVertices.begin(), availableVertices.end(), startingVertices.second), availableVertices.end());

    return {tour1, tour2};
}

// greedy expansion for a single tour
void greedyExpansion(Tour& tour, const std::vector<std::vector<int>>& distanceMatrix, std::vector<int>& availableVertices) {
    int bestInsertPosition = -1;
    int minInsertCost = INT_MAX;
    int bestInsertedVertex = -1;

    for (int vertex : availableVertices) {
        for (size_t i = 0; i <= tour.vertices.size(); ++i) {
            int insertCost = 0;
            if (i > 0) {
                insertCost += distanceMatrix[tour.vertices[i - 1]][vertex];
            }
            if (i < tour.vertices.size()) {
                insertCost += distanceMatrix[vertex][tour.vertices[i]];
            }
            if (i > 0 && i < tour.vertices.size()) {
                insertCost -= distanceMatrix[tour.vertices[i - 1]][tour.vertices[i]];
            }

            if (insertCost < minInsertCost) {
                minInsertCost = insertCost;
                bestInsertPosition = i;
                bestInsertedVertex = vertex;
            }
        }
    }
    // bestInsertPosition = (bestInsertPosition == 0) ? bestInsertPosition+1 : bestInsertPosition;
    tour.vertices.insert(tour.vertices.begin() + bestInsertPosition, bestInsertedVertex);
    availableVertices.erase(std::remove(availableVertices.begin(), availableVertices.end(), bestInsertedVertex), availableVertices.end());
}

// greedy algorithm with random starting vertices
TwoTours greedyAlgorithmRandomStart(const std::vector<std::vector<int>>& distanceMatrix, int tourSize) {
    size_t numVertices = distanceMatrix.size();

    // random choose two distinct starting vertices
    std::pair<int, int> startingVertices = chooseRandomFurthestVertices(numVertices, distanceMatrix);

    // tours initialization with selected starting vertices
    Tour tour1 = {{startingVertices.first}};
    Tour tour2 = {{startingVertices.second}};
    std::pair<Tour, Tour> tours = {tour1, tour2};
    // std::pair<Tour, Tour> tours = initializeToursAndRemoveStartingVertices(startingVertices, distanceMatrix);

    // availableVertices vector initialization
    std::vector<int> availableVertices(numVertices);
    for (size_t i = 0; i < numVertices; ++i) {
        availableVertices[i] = i;
    }
    availableVertices.erase(std::remove(availableVertices.begin(), availableVertices.end(), startingVertices.first), availableVertices.end());
    availableVertices.erase(std::remove(availableVertices.begin(), availableVertices.end(), startingVertices.second), availableVertices.end());

    // greedy expansion for both tours
    while (tours.first.vertices.size() < static_cast<size_t>(tourSize) && tours.second.vertices.size() < static_cast<size_t>(tourSize)) {
        // Tour 1
        greedyExpansion(tours.first, distanceMatrix, availableVertices);

        // Tour 2
        greedyExpansion(tours.second, distanceMatrix, availableVertices);
    }

    return {tours.first, tours.second};
}