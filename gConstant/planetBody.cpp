#include "planetBody.h"
#include<functional>
#include<algorithm>
#include "sceneManager.h"
#include "sun.h"
#include "utils.h"

planetBody::planetBody(double x, double y) : celestialBody()
{
	name = "planet";
	pos = position(x, y);
	utils::println("planet x currently = " + std::to_string(pos.x));
	centreOfRevolution = position(0, 0);
	centreOfRotation = position(x, y);

	this->graphicComponent = sceneManager::drawSphere(x, y, bColor);
	sceneManager::drawTrail(graphicComponent);

}

planetBody::~planetBody()
{

}

void planetBody::move()
{
	auto noOfAttracters = attracters.size();

	if (noOfAttracters > 0)
	{
		std::vector<double> ratioArray(noOfAttracters, 0);

		double wholeValue = 0;
		for (auto& [g, b] : attracters)
			wholeValue += g;

		std::vector<std::pair<gConstant, celestialBody*>> localAttracters(attracters.begin(), attracters.end());
		for (int i(0); i < noOfAttracters; i++)
		{
			gConstant gi = (*(localAttracters.begin() + i)).first; //gConstant value of ith element in map
			ratioArray[i] = gi / wholeValue;
		}
		position curPos = this->pos;

		position pi;
		std::pair<gConstant, celestialBody*> bi;
		for (int i(0); i < noOfAttracters; i++)
		{
			bi = *(localAttracters.begin() + i);
			pi = bi.second->pos;								//pos value of ith sun in map
			curPos = (curPos + (pi - curPos) * ratioArray[i]) * (this->getMass() / bi.second->getMass());
		}

		//best revolvearound body
		decltype(bi.second) best(bi.second);
		for (int i(0); i < noOfAttracters; i++)
		{
			auto bj = *(localAttracters.begin() + i);
			auto dist = utils::distance(bj.second->pos, this->pos);
			if ((dist > bj.second->getOrbitalDistance()) and (dist < best->getOrbitalDistance()))
				if (bj.second->getGravity() > getGravity())
					best = bj.second;
		}
		//bi is currently the body with maximum g value : usually sun
		position delta, newPos;

		newPos = pos + ((curPos - pos) / 98);
		auto
			dist = utils::distance(best->pos, this->pos) - size,
			dist2 = utils::distance(best->pos, newPos) - size;

		if ((dist > best->getOrbitalDistance()) and (dist2 > best->getOrbitalDistance())) //distance of pos greater than orbitalDistance
		{
			auto prevPos = pos;

			utils::println("pos before division (" + std::to_string(pos.x) + std::string(",") + std::to_string(pos.y));
			pos = newPos;

			delta = pos - prevPos;
			direction = (delta.x >= 0 or delta.y >= 0) ? CLOCKWISE: ANTICLOCKWISE;
		}
		else
		{
			utils::println("posx before revolution" + std::to_string(pos.x) + std::string(",") + std::to_string(pos.y));
			revolveAround(best, direction); //best should be the best contender (within orbital distance and order by gravity)
			utils::println("posx after revolution" + std::to_string(pos.x) + std::string(",") + std::to_string(pos.y));
		}
	}
}