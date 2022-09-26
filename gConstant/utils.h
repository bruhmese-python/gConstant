#pragma once
#include<cmath>
#include <iostream>
#include <sstream>
#include "position.h"

#define CLOCKWISE 1
#define ANTICLOCKWISE -1

struct position;

namespace utils
{
	double distance(position a, position b);

	template <typename... S1>
	auto helperSum(S1... s);
	
	int randInRange(int min,int max);

	void println(std::string text);

};

