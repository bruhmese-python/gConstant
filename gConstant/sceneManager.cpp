#include "sceneManager.h"
#include <iostream>
#include <string>
#include "celestialBody.h"
#include "driverChoice.h"
#include "MyEventReceiver.h"

bool sceneManager::playScene = true;
bool sceneManager::pencilDrawings = true;
std::set<celestialBody *> sceneManager::celestialBodies = {};

IrrlichtDevice *sceneManager::device;
IVideoDriver *sceneManager::driver;
ISceneManager *sceneManager::smgr;
IGUIEnvironment *sceneManager::guienv;
IGUIStaticText *sceneManager::text;

void sceneManager::registerBody(celestialBody *body)
{
	sceneManager::celestialBodies.insert(body);
}

void sceneManager::drawTrail(ISceneNode *b)
{
	scene::IParticleSystemSceneNode *ps =
		sceneManager::smgr->addParticleSystemSceneNode(false, 0, -1);

	scene::IParticleEmitter *em = ps->createPointEmitter(
		core::vector3df(0.0f, 0.0f, 0.0f), // initial direction
		50, 50,							   // emit rate
		video::SColor(0, 255, 255, 255),   // darkest color
		video::SColor(0, 255, 255, 255),   // brightest color
		10000, 10000, 0,				   // min and max age, angle
		core::dimension2df(0.25f, 0.25f),  // min size
		core::dimension2df(0.25f, 0.25f)); // max size

	ps->setEmitter(em);
	em->drop();
	scene::IParticleAffector *paf = ps->createFadeOutParticleAffector();
	ps->addAffector(paf);
	paf->drop();

	ps->setMaterialFlag(video::EMF_LIGHTING, false);
	ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	ps->setParent(b);
}

void sceneManager::mainLoop()
{

	for (celestialBody *each : celestialBodies)
		each->trigger();
}

void sceneManager::_init_()
{
	device = createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
						  false, false, false, 0);

	if (!device)
		exit(1);

	device->setWindowCaption(L"gConstant");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	auto skin = guienv->createSkin(EGUI_SKIN_TYPE::EGST_BURNING_SKIN);
	guienv->setSkin(skin);

	text = guienv->addStaticText(L"", rect<s32>(10, 10, 260, 500), true);

	auto checkRect = recti(vector2di(500, 400), vector2di(640, 480));
	// driver->draw2DRectangle(SColor(255,255,255,255), checkRect);
	IGUIWindow *window = guienv->addWindow(checkRect, false, // modal?
										   L"Variables");
	IGUICheckBox *checkbox = guienv->addCheckBox(true, recti(vector2di(5, 20), vector2di(55, 40)), window, GUI_ID_PENCIL_DRAWINGS, L"Pencil Drawings");
	IGUICheckBox *checkbox2 = guienv->addCheckBox(true, recti(vector2di(5, 42), vector2di(55, 62)), window, GUI_ID_PENCIL_DRAWINGS, L"Log");

	drawGrid();

	// Store the appropriate data in a context structure.
	SAppContext context;
	context.device = device;
	context.counter = 0;
	context.pencilCheck = checkbox;

	// Then create the event receiver, giving it that context structure.
	MyEventReceiver *receiver = new MyEventReceiver(context);

	// And tell the device to use our custom event receiver.
	device->setEventReceiver(receiver);

	skin->drop();
}

IBillboardSceneNode *sceneManager::drawGlow(ISceneNode *b)
{
	scene::IBillboardSceneNode *bill = smgr->addBillboardSceneNode(b);
	bill->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	bill->setMaterialTexture(0, driver->getTexture("sphereGlow.png"));
	bill->setMaterialFlag(video::EMF_LIGHTING, false);

	bill->setParent(b);
	return bill;
}

ISceneNode *sceneManager::drawSphere(double x, double y, irr::video::SColor bgColor)
{
	ISceneNode *emptyParent = smgr->addEmptySceneNode();
	emptyParent->setPosition(position(x, y).p_vector());

	IAnimatedMesh *mesh = smgr->getMesh("sphere.b3d");
	if (!mesh)
	{
		device->drop();
		std::cout << "Could not draw mesh";
	}
	IAnimatedMeshSceneNode *node = smgr->addAnimatedMeshSceneNode(mesh);

	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialTexture(0, driver->getTexture("sphereTex.png"));
		node->setParent(emptyParent);

		return emptyParent;
	}
	else
		return nullptr;
}
void sceneManager::drawGrid()
{
	IAnimatedMesh *mesh = smgr->getMesh("grid.b3d");
	if (!mesh)
	{
		device->drop();
		std::cout << "Could not draw mesh";
	}
	IAnimatedMeshSceneNode *node = smgr->addAnimatedMeshSceneNode(mesh);

	if (node)
	{
		node->setMaterialFlag(EMF_USE_MIP_MAPS, false);
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
		node->setMaterialTexture(0, driver->getTexture("3dgrid.png"));

		node->setPosition(node->getPosition() + vector3df(0, -50, 0));
		node->setScale(vector3df(5, 5, 5));
	}
}

void sceneManager::drawLine(celestialBody *a, celestialBody *b)
{
	if (pencilDrawings == false)
		return;

	SMaterial mtl;
	mtl.EmissiveColor = b->bColor;
	driver->setMaterial(mtl);

	driver->setTransform(video::ETS_WORLD, core::IdentityMatrix);
	driver->draw3DLine(a->graphicComponent->getPosition(), b->graphicComponent->getPosition(), a->bColor);
}

void sceneManager::drawBox(celestialBody *a)
{
	if (pencilDrawings == false)
		return;

	SMaterial mtl;
	mtl.EmissiveColor = a->bColor;
	driver->setMaterial(mtl);

	auto size = a->size;
	auto pos = a->pos;
	sceneManager::driver->setTransform(video::ETS_WORLD, core::IdentityMatrix);
	sceneManager::driver->draw3DBox(
		irr::core::aabbox3df(
			(pos - position(size, size)).p_vector(), (pos + position(size, size)).p_vector()),
		a->bColor);
}

void sceneManager::drawCircle(celestialBody *a, float r, int intensity)
{
	if (pencilDrawings == false)
		return;

	SMaterial mtl;
	int iColor = 255 / intensity;
	mtl.EmissiveColor = SColor(255, iColor, iColor, iColor);
	driver->setMaterial(mtl);

	auto pos = a->pos;
	sceneManager::driver->setTransform(video::ETS_WORLD, core::IdentityMatrix);
	sceneManager::driver->draw3DBox(
		irr::core::aabbox3df(
			(pos - position(r, r)).p_vector(), (pos + position(r, r)).p_vector()),
		a->bColor);
}