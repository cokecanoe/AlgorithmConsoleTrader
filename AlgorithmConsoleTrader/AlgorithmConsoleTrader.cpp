// AlgorithmConsoleTrader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <random> // For random number generation
#include <algorithm> // For std::max_element
#include <string>
#include "ForexDataTypes.h"
#include "CalculateSupportResistance.h"
#include "PlotDataAsGraph.h"
#include "CalculateAverageGainOrLoss.h"
using namespace std;



int main()
{
    // Create a vector to store the dataset
    std::vector<ForexData> dataset;

    // Get the current time
    std::time_t currentTime;
    std::tm currentTm = {};
    currentTime = std::time(nullptr);

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> priceDist(1.1000, 1.2000); // Adjust the price range as needed

    for (int i = 0; i < 20; ++i) {
        // Calculate timestamps for each data point with 1-hour intervals
        if (localtime_s(&currentTm, &currentTime) != 0) {
            std::cerr << "Failed to get local time." << std::endl;
            return 1; 
        }
        currentTm.tm_hour += i;
        std::mktime(&currentTm);  // Normalize the time

        // Format date and time using std::stringstream
        std::stringstream dateStream, timeStream;
        dateStream << std::setfill('0') << std::setw(4) << (currentTm.tm_year + 1900) << "-"
            << std::setfill('0') << std::setw(2) << (currentTm.tm_mon + 1) << "-"
            << std::setfill('0') << std::setw(2) << currentTm.tm_mday;
        timeStream << std::setfill('0') << std::setw(2) << currentTm.tm_hour << ":"
            << std::setfill('0') << std::setw(2) << currentTm.tm_min << ":"
            << std::setfill('0') << std::setw(2) << currentTm.tm_sec;

        ForexData data;
        data.date = dateStream.str();
        data.time = timeStream.str();
        data.symbol = "EUR/USD";

        // Generate randomized bid/ask/last prices
        data.bidPrice = priceDist(gen);
        data.askPrice = data.bidPrice + 0.0001; // Assuming a spread of 0.0001
        data.lastPrice = priceDist(gen);

        data.volume = 1000 + i * 50;

        dataset.push_back(data);
    }

    // Print the generated dataset
    std::cout << "Currency Pair Prices Over 20 Time Points:" << std::endl;
    for (const ForexData& data : dataset) {
        std::cout << "Date: " << data.date << " Time: " << data.time
            << " Symbol: " << data.symbol << " Bid Price: " << std::fixed << std::setprecision(4) << data.bidPrice
            << " Ask Price: " << std::fixed << std::setprecision(4) << data.askPrice
            << " Last Price: " << std::fixed << std::setprecision(4) << data.lastPrice
            << " Volume: " << data.volume << std::endl;
    }

   

     // Extract bid prices from the dataset for plotting
    std::vector<double> bidPrices;
    for (const ForexData& data : dataset) {
        bidPrices.push_back(data.bidPrice);
    }

    // Plot the line graph of bid prices
    plotLineGraph(bidPrices);

    CalculateSR(dataset);
     hasThreeOrMoreResistance(dataset);
     hasThreeOrMoreSupport(dataset);

     CalculateAvgGainOrLoss(dataset);
    

   
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
