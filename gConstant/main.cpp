#include <iostream>
#include "planetBody.h"
#include "sun.h"
#include "sceneManager.h"
#include <chrono>
#include <thread>
//int main()
//{
//    planetBody P;
//    
//    std::cout << "Hello world";
//    return 0;
//}

using namespace sceneManager;

int main()
{
	sceneManager::_init_();

	auto spacebg = sceneManager::driver->getTexture("space_bg.png");
	auto size = spacebg->getSize();
	auto imgX = size.Width, imgY = size.Height;

	planetBody p(-15, 0);
	p.getMass() = 2;
	p.getGravity() = 9.8;
	p.setForceField(2);
	p.setSize();

	planetBody a(14, -14);
	a.getMass() = 1;
	a.getGravity() = 9.8;
	a.setForceField(4);
	a.setSize();
	
	planetBody x(-3, -3);
	x.getMass() = 2;
	x.getGravity() = 20;
	x.setForceField(5);
	x.setSize();

	planetBody y(-12, -16);
	y.getMass() = 2;
	y.getGravity() = 12;
	y.setForceField(10);
	y.setSize();


	sun s(0, -30);
	s.setForceField(200);
	s.getGravity() = 20;
	s.getMass() = 5;
	s.setSize();

	sun s2(0, 150);
	s2.name = "sun2";
	s2.setForceField(1000);
	s2.getGravity() = 10;
	s2.getMass() = 5;
	s2.setSize();

	//x : y, y : z ,z : x
	//smgr->addCameraSceneNode(0, vector3df(50, 0, 0), vector3df(0, 0, 0));
	//smgr->addCameraSceneNodeFPS();
	auto cam = smgr->addCameraSceneNodeMaya();
	cam->setTarget(a.graphicComponent->getAbsolutePosition());

	while (device->run())
	{
		driver->beginScene(true, true, SColor(255, 100, 101, 140));
		driver->draw2DImage(spacebg, rect<s32>(0, 0, 640, 480), rect<s32>(0, 0, imgX, imgY)); //draw background

		sceneManager::mainLoop();

		smgr->drawAll();
		guienv->drawAll();

		//using namespace std::literals::chrono_literals;s
		//std::chrono::high_resolution_clock::now();
		//std::this_thread::sleep_for(0.1s);

		driver->endScene();
	}

	device->drop();

	return 0;
}
