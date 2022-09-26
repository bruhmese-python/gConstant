#ifndef SUN_H
#define SUN_H

#include "celestialBody.h"
#include "insertable.h"

#pragma once
class sun :public celestialBody, public insertable
{
private:
	IBillboardSceneNode* glowNode;
public:
	position centreOfRotation;

	void move();
	virtual void setSize() override;

	sun(double, double);
	~sun();
};

#endif

