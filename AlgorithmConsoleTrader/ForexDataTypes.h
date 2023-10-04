#pragma once
#include <iostream>

using namespace std;

struct ForexData {
    std::string date;
    std::string time;
    std::string symbol;
    double bidPrice;
    double askPrice;
    double lastPrice;
    int volume;
};

struct PricesHighAndLow {
    double priceHigh;
    double priceLow;
};

struct AverageLossAndGain {
    double avgFouteenDayGain[20];
    double avgFourteenDayLoss[20];
};

