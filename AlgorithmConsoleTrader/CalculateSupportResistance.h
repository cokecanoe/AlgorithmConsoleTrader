#pragma once
#include <iostream>
#include "ForexDataTypes.h"

using namespace std;

int CalculateSR(const std::vector<ForexData>& dataset) {

    // Define variables for support and resistance levels
    double supportLevel = dataset[0].bidPrice;
    double resistanceLevel = dataset[0].bidPrice;

    // Iterate through the dataset to find support and resistance levels
    for (const ForexData& data : dataset) {
        // Update support level if the bid price is lower
        if (data.bidPrice < supportLevel) {
            supportLevel = data.bidPrice;
        }
        // Update resistance level if the bid price is higher
        else if (data.bidPrice > resistanceLevel) {
            resistanceLevel = data.bidPrice;
        }
    }

    // Print the support and resistance levels
    std::cout << "Support Level: " << std::fixed << std::setprecision(4) << supportLevel << std::endl;
    std::cout << "Resistance Level: " << std::fixed << std::setprecision(4) << resistanceLevel << std::endl;

    return 0;
}

PricesHighAndLow findHighestAndLowestPrices(const std::vector<ForexData>& dataset) {

    // Initialize the highest and lowest prices with the first bid price
    double highestPrice = dataset[0].bidPrice;
    double lowestPrice = dataset[0].bidPrice;

    // Iterate through the dataset to find the highest and lowest prices
    for (const ForexData& data : dataset) {
        double currentBidPrice = data.bidPrice;

        if (currentBidPrice > highestPrice) {
            highestPrice = currentBidPrice;
        }

        if (currentBidPrice < lowestPrice) {
            lowestPrice = currentBidPrice;
        }
    }

    PricesHighAndLow prices;
    prices.priceHigh = highestPrice;
    prices.priceLow = lowestPrice;

    return prices;
}

// Function to check if there are 3 or more bid prices within 1/100th of each other
bool hasThreeOrMoreResistance(const std::vector<ForexData>& dataset) {
    double epsilon = 0.01;   // 1/1000th
    int count = 0; // Count of similar bid prices


    PricesHighAndLow pricesLowAndHigh = findHighestAndLowestPrices(dataset);

    for (size_t a = 0; a < dataset.size(); ++a) {
        double price = dataset[a].bidPrice;

        if (std::abs(pricesLowAndHigh.priceHigh - price) <= epsilon && price != pricesLowAndHigh.priceHigh) {
            cout << std::abs(pricesLowAndHigh.priceHigh - price) << endl;
            count++;
        }

        if (count >= 3) {
            cout << "There is resistance" << endl;
            return true;
        }

    }

    return false; // No 3 or more similar bid prices found
}

bool hasThreeOrMoreSupport(const std::vector <ForexData>& dataset) {

    double epsilon = 0.01;   // 1/1000th
    int count = 0; // Count of similar bid prices


    PricesHighAndLow pricesLowAndHigh = findHighestAndLowestPrices(dataset);
    for (size_t b = 0; b < dataset.size(); ++b) {
        double price = dataset[b].bidPrice;

        if (std::abs(price - pricesLowAndHigh.priceLow) <= epsilon && price != pricesLowAndHigh.priceLow) {
            cout << std::abs(price - pricesLowAndHigh.priceLow) << endl;
            count++;
        }

        if (count >= 3) {
            cout << "There is support" << endl;
            return true;
        }
    }

    return false; // No 3 or more similar bid prices found
}


//rules:
// determine a support or resistance baseline by gatherin prices within the 1/100th of the price. 
//determine if this price holds, (does the price break the support/resistance line often
//if the price hold consecutively, we can conclude that there is support if the line is broken often this is not a support or resistance indicator.
//find to peak high and low to determine this. 
//only lok for support amoung the price high and price low over the course of the graph.

