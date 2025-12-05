
//------------------------------------------------------------------------------

#include "Tank2007.h"

#include "Console.h"

//------------------------------------------------------------------------------

Console::Console() : mConsole(NULL), mConsoleLog(NULL), mItem(NULL)
{
}

//------------------------------------------------------------------------------

void Console::init()
{
	mConsole = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Console");
	mConsoleLog = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Console/Log");
}

//------------------------------------------------------------------------------

void Console::write(const std::string& msg)
{
	mItem = new CEGUI::ListboxTextItem(msg);

	mConsoleLog->addItem(mItem);
	mConsoleLog->ensureItemIsVisible(mItem);
}

//------------------------------------------------------------------------------

void Console::toggleVisible()
{
	mConsole->setVisible(!mConsole->isVisible());
}

//------------------------------------------------------------------------------
