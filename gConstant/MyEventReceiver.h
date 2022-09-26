#pragma once
#include "irrlicht.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

struct SAppContext
{
	IrrlichtDevice* device;
	s32             counter;
	IGUICheckBox* pencilCheck;
};

class MyEventReceiver : public IEventReceiver
{
private:
	SAppContext& Context;
public:
	MyEventReceiver(SAppContext& context);

	virtual bool OnEvent(const SEvent& event);
};