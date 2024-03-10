#pragma once
#include <vector>
#include "distance_calculation.h"

std::vector<Point> readNodeCoordinates(const char* file_path);
void saveDistanceMatrixToFile(const std::vector<std::vector<int>>& distanceMatrix, const char* file_name);