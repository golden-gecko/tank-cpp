
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Tank2007.h"

//------------------------------------------------------------------------------

class Console : public Ogre::Singleton<Console>
{
	private:

		CEGUI::FrameWindow*		mConsole;
		CEGUI::Listbox*			mConsoleLog;
		CEGUI::ListboxTextItem*	mItem;

	public:

		Console();

		void init();

		void write(const std::string& msg);

		void toggleVisible();
};

//------------------------------------------------------------------------------
