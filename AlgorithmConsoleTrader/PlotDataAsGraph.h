#pragma once
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <random> // For random number generation
#include <algorithm> // For std::max_element
#include <string>
#include "ForexDataTypes.h"
#include "CalculateSupportResistance.h"

void plotLineGraph(const std::vector<double>& data) {
    // Find the maximum and minimum values in the data for scaling
    double maxData = *std::max_element(data.begin(), data.end());
    double minData = *std::min_element(data.begin(), data.end());

    // Define the height of the plot area
    const int plotHeight = 10; // Adjust the height as needed

    // Calculate scaling factor for data points
    double yScale = static_cast<double>(plotHeight) / (maxData - minData);

    // Create a 2D grid to represent the plot
    std::vector<std::vector<char>> plot(plotHeight, std::vector<char>(data.size(), ' '));

    // Plot data points on the grid
    for (size_t i = 0; i < data.size(); ++i) {
        int y = static_cast<int>((data[i] - minData) * yScale);

        // Ensure the Y-coordinate is within the plot area
        if (y >= 0 && y < plotHeight) {
            plot[plotHeight - y - 1][i] = '*';
        }
    }

    // Print the plot to the terminal
    for (int i = 0; i < plotHeight; ++i) {
        for (size_t j = 0; j < data.size(); ++j) {
            std::cout << plot[i][j];
        }
        std::cout << std::endl;
    }
}