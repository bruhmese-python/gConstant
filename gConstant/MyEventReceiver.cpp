#include "MyEventReceiver.h"

namespace sceneManager
{
	extern IrrlichtDevice* device;
	extern enum GUI_CONSTANTS {
		GUI_ID_PENCIL_DRAWINGS,
		GUI_ID_LOG
	};
	extern bool pencilDrawings;
	extern IGUIStaticText* text;
};

MyEventReceiver::MyEventReceiver(SAppContext& context) : Context(context) { this->Context = context; }

bool MyEventReceiver::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();
		IGUIEnvironment* env = sceneManager::device->getGUIEnvironment();

		switch (event.GUIEvent.EventType)
		{
		case sceneManager::GUI_ID_PENCIL_DRAWINGS:
			sceneManager::pencilDrawings = sceneManager::pencilDrawings == false ? true : false;
			break;
		case sceneManager::GUI_ID_LOG:
			sceneManager::text->isVisible() ? sceneManager::text->setVisible(false) : sceneManager::text->setVisible(true);
			break;
		default:
			break;
		}
	}

	return false;
}
