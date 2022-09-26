#include "sun.h"
#include<string>

namespace utils
{
	void println(std::string);
};

void sun::move()
{
}

void sun::setSize()
{
	celestialBody::setSize();

	auto scaleX(graphicComponent->getScale().X), scaleY(graphicComponent->getScale().Y);
	
	auto sizeC(glowNode->getSize());
	glowNode->setSize(dimension2df(scaleX * sizeC.Width, scaleY * sizeC.Height));
}

sun::sun(double x, double y) : celestialBody()
{
	name = "sun";
	pos = position(x, y);
	utils::println("sun x currently = " + std::to_string(pos.x));
	centreOfRotation = position(x, y);
	graphicComponent = sceneManager::drawSphere(x, y);
	glowNode = sceneManager::drawGlow(graphicComponent);

}

sun::~sun()
{
}
