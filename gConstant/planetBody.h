#ifndef PLANETBODY_H
#define PLANETBODY_H

#include "celestialBody.h"
#include <map>

#pragma once

class planetBody : public celestialBody
{
private:
	int direction = 1;
public:
	planetBody(double, double);
	~planetBody();

	void move();

	position centreOfRevolution;
	position centreOfRotation;
};

#endif