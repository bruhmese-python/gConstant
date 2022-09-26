#include "celestialBody.h"
#include "sceneManager.h"
#include <numeric>
#include <algorithm>
#include <set>
#include "utils.h"
#include "sun.h"

void celestialBody::setSize()
{
	size = (gravity * mass) / 9.8;
	graphicComponent->setScale(irr::core::vector3df(size, size, size));
}

celestialBody::celestialBody() : pos(0.0f, 0.0f), mass(1.0f), graphicComponent(nullptr), rayDistance(1)
{
	bColor = SColor(
		utils::randInRange(0, 255),
		utils::randInRange(0, 255),
		utils::randInRange(0, 255),
		utils::randInRange(0, 255)
	);
	sceneManager::registerBody(this);
}
celestialBody::~celestialBody()
{
}

void celestialBody::setForceField(float _rayDistance)
{
	rayDistance = _rayDistance;
	orbitalDistance = _rayDistance * 0.75f;
}


void celestialBody::addAttracter(celestialBody* b)
{
	if (this->_attracters.find(b) == _attracters.end()) //if not in _attracters
	{
		//utils::println("Adding an attracter to " + name);
		_attracters.insert(b);
		attracters.insert(std::make_pair(b->getGravity(), b));
	}
}
void celestialBody::updateAttracters()
{
	//utils::println("Attracters before updation " + std::to_string(attracters.size()));

	for (celestialBody* f_body : _attracters)
	{
		if (not (utils::distance(f_body->pos, this->pos) < f_body->getRayDistance()))
		{
			//to find and remove (remove_if not working)
			auto f_it = attracters.begin();
			for (auto& [g, b] : attracters)
			{
				if (b == f_body)
					break;
				f_it++;
			}
			if (f_it != attracters.end())
			{
				//utils::println("Removing " + f_it->second->name + "from " + this->name);
				attracters.erase(f_it);
			}
		}
	}
	_attracters.clear();
	for (auto& [g, b] : attracters)
		_attracters.insert(b);

	//utils::println("Attracters after updation " + std::to_string(attracters.size()));

	for (auto& b : _attracters)
	{
		sceneManager::drawLine(this, b);
	}
}

position rotate_point(float cx, float cy, float angle, position p)
{
	//utils::println("rotating around point " + std::to_string(cx) + ", " + std::to_string(cy));

	angle = irr::core::degToRad(angle);

	float s = sin(angle);
	float c = cos(angle);

	p.x -= cx;
	p.y -= cy;

	float xnew = p.x * c - p.y * s;
	float ynew = p.x * s + p.y * c;

	p.x = xnew + cx;
	p.y = ynew + cy;
	return p;
}

void celestialBody::revolveAround(celestialBody* b, int direction)
{
	auto totalMass = b->mass + this->mass;
	auto angle = mass / totalMass;
	this->pos = rotate_point(b->pos.x, b->pos.y, angle * direction, this->pos);
}

void celestialBody::catchAny()
{
	std::vector<celestialBody*> closeBodies;
	auto& cB = sceneManager::celestialBodies;
	//utils::println("celestial bodies : " + std::to_string(sceneManager::celestialBodies.size()));

	std::copy_if(cB.begin(), cB.end(), std::back_inserter(closeBodies),
		[this](const auto& b) {

			auto d = utils::distance(this->pos, b->pos) - b->getOrbitalDistance();
			auto rDist = this->getRayDistance();

			//utils::println("distance btw " + this->name + std::string(" & ") + b->name + std::to_string(d));
			//utils::println("(this) " + name + " raydistance " + std::to_string(rDist) + std::string(" > ") + std::to_string(d));

			return ((d < rDist) and (this not_eq b));
		}
	);

	//utils::println("caught " + std::to_string(closeBodies.size()) + " closeBodies");

	for (celestialBody* each : closeBodies)
	{
		sceneManager::drawBox(each);
		//utils::println("compare mass (this) " + name + std::to_string(this->getMass()) + " > " + std::to_string(each->getMass()));
		if (each->getMass() < this->getMass())
		{
			each->addAttracter(this);
		}
	}
}

void celestialBody::trigger()
{
	this->catchAny();
	this->updateAttracters();
	this->move();
	this->graphicComponent->setPosition(pos.p_vector());
	sceneManager::drawCircle(this, getRayDistance(), sceneManager::CircleIntensity::LOW);
	sceneManager::drawCircle(this, getOrbitalDistance(), sceneManager::CircleIntensity::HIGH);
}
gConstant& celestialBody::getGravity() /*const*/ { return gravity; }
float& celestialBody::getMass() /*const */ { return mass; }
float celestialBody::getOrbitalDistance() { return orbitalDistance; }
float celestialBody::getRayDistance() { return rayDistance; }