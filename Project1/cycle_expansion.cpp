#include <sstream>
#include <iomanip> 
#include <limits>
#include <filesystem>
#include <cmath>
#include <iostream>
#include "vertex_manager.h"
#include "graph_builder.h"
#include "file_management.h"

void cycleExpansionAlgorithm(const std::vector<std::vector<int>>& distanceMatrix) {
    int numRows;
        int numGraphRows;
        std::vector<bool> isInGraph(numRows, false);
        Result result;
        std::vector<std::vector<int>> graph;
        int totalCycleLength;
        std::string filename;
        std::stringstream ss1;
        std::stringstream ss2;
        int sumCycles; 
        int minCycle = std::numeric_limits<int>::max();
        int minIteration;
        int maxCycle = -1;
        int maxIteration;
        int avgCycle = 0;
        float numOfIterations = 100.0;

        std::filesystem::create_directory("results");

        for (int i = 0; i < numOfIterations; i++) {

            // suma długości obu cykli
            sumCycles = 0;

            // weź liczbę wierzchołków
            numRows = distanceMatrix.size();
            // ustal liczbę wierzchołków dla pierwszego grafu
            numGraphRows = numRows / 2 + (numRows % 2);
            
            // stwórz tablicę o rozmiarze równym liczbie wierzchołków, ustal wartości początkowe na False (żaden wierzchołek nie jest jeszcze w grafie)
            isInGraph.assign(numRows, false);

            // stwórz pierwszy graf
            result = GraphBuilder::buildGraph(distanceMatrix, isInGraph, numGraphRows);

            // pobierz wynikowy graf
            graph = result.graph;
            // pobierz tablicę użytych wierzchołków
            isInGraph = result.isInGraph;
            // pobierz całkowitą długość cyklu

            // wyświetl rezultat dla grafu 1
            totalCycleLength = result.totalLength;
            sumCycles = sumCycles + totalCycleLength;

            // nazwa pliku
            ss1 << "results/graph" << 1 << "_" << i << ".txt";
            filename = ss1.str();

            // wpisz do pliku
            writeVerticesToFile(graph, totalCycleLength, filename);

            // oblicz ilość wierzchołków w drugim grafie
            numGraphRows = numRows - numGraphRows;

            // stwórz drugi graf
            result = GraphBuilder::buildGraph(distanceMatrix, isInGraph, numGraphRows);

            // pobierz dane dla drugiego grafu
            graph = result.graph;
            isInGraph = result.isInGraph;
            totalCycleLength = result.totalLength;
            sumCycles = sumCycles + totalCycleLength;

            ss2 << "results/graph" << 2 << "_" << i << ".txt";
            filename = ss2.str();

            writeVerticesToFile(graph, totalCycleLength, filename);

            // reset obu stringstreams żeby z każdą iteracją były inne nazwy plików
            std::stringstream().swap(ss1);
            std::stringstream().swap(ss2);

            // szukanie minimalnej i maksyalnej długości cyklu
            if (minCycle > sumCycles) {
                minCycle = sumCycles;
                minIteration = i;
            }
            if (maxCycle < sumCycles) {
                maxCycle = sumCycles;
                maxIteration = i;
            }
            // sumowanie dł. cykli do późniejszego obliczenia średniej długości cyklu
            avgCycle = avgCycle + sumCycles;
        }
        // obliczanie średniej długości cykli
        avgCycle = std::round(avgCycle / numOfIterations);

        std::cout << "Min sum of both cycles is: " << minCycle << " for iteration " << minIteration << '\n';
        std::cout << "Max sum of both cycles is: " << maxCycle << " for iteration " << maxIteration << '\n';
        std::cout << "Average sum of both cycles is: " << avgCycle << '\n';

    return;
}