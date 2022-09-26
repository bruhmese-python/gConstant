#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include<vector>
#include <irrlicht.h>
#include<set>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


class celestialBody;

#pragma once
namespace sceneManager
{
	extern bool pencilDrawings;
	extern bool playScene;
	extern std::set<celestialBody*> celestialBodies;

	//Graphics library integration
	extern IrrlichtDevice* device;
	extern IVideoDriver* driver;
	extern ISceneManager* smgr;
	extern IGUIEnvironment* guienv;
	extern IGUIStaticText* text;

	enum GUI_CONSTANTS {
		GUI_ID_PENCIL_DRAWINGS = 0x10000,
		GUI_ID_LOG
	};

	enum CircleIntensity { HIGH = 1, MID, LOW };

	/// Initialize parameters of graphics context
	void _init_();

	/// Draw Blender style 3d grid
	void drawGrid();

	/// Draws a planet sphere onto the screen
	ISceneNode* drawSphere(double x = 0, double y = 0, SColor = SColor(255,0,0,0));

	void drawTrail(ISceneNode*);

	///Draws connector
	void drawLine(celestialBody*, celestialBody*);

	///Draws glow around planet
	IBillboardSceneNode* drawGlow(ISceneNode* b);

	/// Draws 3d box
	void drawBox(celestialBody* a);

	/// Draws circle
	void drawCircle(celestialBody*, float, int);

	/// Register a new body in the stack
	void registerBody(celestialBody* body);

	/// Holds looped instructions to execute in intervals
	void mainLoop();
};

#endif

