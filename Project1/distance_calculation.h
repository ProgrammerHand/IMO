#pragma once
#include <vector>

struct Point {
    double x, y;
};

int calculateRoundedDistance(const Point& p1, const Point& p2);
std::vector<std::vector<int>> calculateDistanceMatrix(const std::vector<Point>& nodes);
void printDistanceMatrix(const std::vector<std::vector<int>>& distanceMatrix);