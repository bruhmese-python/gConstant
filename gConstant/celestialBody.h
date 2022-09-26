#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include<vector>
#include<map>
#include<string>
#include<set>
#include "position.h"
#include "irrlicht.h"
#pragma once

using gConstant = float;

class sun; //forward declared

class celestialBody
{
private:
	gConstant gravity;
	float mass;

	std::set<celestialBody*> _attracters;
public:
	float size;
	virtual void setSize();

	std::string name;
	float rayDistance;
	float orbitalDistance;
	irr::video::SColor bColor;

	celestialBody();
	~celestialBody();

	position pos; // same as centre of gravity
	irr::scene::ISceneNode* graphicComponent;

	float getOrbitalDistance();
	float getRayDistance();
	void setForceField(float);

	void addAttracter(celestialBody*);
	void updateAttracters();
	virtual void move() = 0;
	void revolveAround(celestialBody*, int);
	//virtual void updateGraphic() = 0;

	void catchAny();
	virtual void trigger();

	gConstant& getGravity() /*const*/;
	float& getMass() /*const*/;

	std::multimap<gConstant, celestialBody*> attracters;
};

#endif