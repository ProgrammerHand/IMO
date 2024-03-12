#pragma once
#include <vector>

class RandomElement {
public:
    static int get_random_node(const std::vector<std::vector<int>>& matrix);
    static int find_closest_node(const std::vector<std::vector<int>>& distanceMatrix, int chosenRowIndex, std::vector<bool> isInGraph);
    static int create_cycle(const std::vector<std::vector<int>>& distanceMatrix, int randomRowIndex, int closestNodeIndex, std::vector<bool> isInGraph);
};



