#pragma once

#include <iostream>
#include <vector>
#include "ForexDataTypes.h"

using namespace std;



void CalculateAvgGainOrLoss(const std::vector<ForexData>& dataset, double testData = { 0 }) {

	

	double strongDownward[20] = {1.1001, 1.1003, 1.1005, 1.1008, 1.1012, 1.1017, 1.1022, 1.1027, 1.1032, 1.1038,
1.1045, 1.1052, 1.1060, 1.1069, 1.1079, 1.1090, 1.1102, 1.1115, 1.1129, 1.1144 }; //use this test data later

	double strongUpward[20] = {1.1144, 1.1141, 1.1137, 1.1133, 1.1128, 1.1123, 1.1117, 1.1111, 1.1104, 1.1096,
1.1088, 1.1079, 1.1070, 1.1060, 1.1050, 1.1039, 1.1027, 1.1014, 1.1000, 1.0985 }; //use this test data later

	
	int numIncrease = 0;

	double sumIncrease = 0.0;

	for (size_t i = 1; i < dataset.size(); i++) {
		double increase = dataset[i].bidPrice - dataset[i - 1].bidPrice;
		sumIncrease += increase;
		numIncrease++;
	}

	double averageIncreaseDecrease = sumIncrease / numIncrease;

	if (averageIncreaseDecrease < 0) {
		cout << "Sum of decreases: " << sumIncrease << std::endl;
		cout << "Number of decreases: " << numIncrease << std::endl;
		cout << "Average decrease: " << averageIncreaseDecrease << std::endl;
	}
	else {
		cout << "Sum of increases: " << sumIncrease << std::endl;
		cout << "Number of increases: " << numIncrease << std::endl;
		cout << "Average increase: " << averageIncreaseDecrease << std::endl;
	}

	
}

//this gives us the average increase or decrease over the entire set of data given.
//we will also check what kind of number will predict a higher chance of trend continuation. 