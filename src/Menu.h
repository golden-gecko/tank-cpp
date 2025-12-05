
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Tank2007.h"

//------------------------------------------------------------------------------

class Menu : public Ogre::Singleton<Menu>
{
	private:

		CEGUI::FrameWindow*	mMenuMain;
		CEGUI::FrameWindow*	mMenuStartGame;
		CEGUI::FrameWindow*	mMenuJoinGame;
		CEGUI::FrameWindow*	mMenuOptions;

		CEGUI::PushButton*	mMenuMainStartGame;
		CEGUI::PushButton*	mMenuMainJoinGame;
		CEGUI::PushButton*	mMenuMainReturnToGame;
		CEGUI::PushButton*	mMenuMainOptions;
		CEGUI::PushButton*	mMenuMainQuit;

		CEGUI::PushButton*	mMenuStartGameStart;

		CEGUI::PushButton*	mMenuJoinGameJoin;

		bool menuMainStartGame_MouseClick(const CEGUI::EventArgs& args);
		bool menuMainJoinGame_MouseClick(const CEGUI::EventArgs& args);
		bool menuMainReturnToGame_MouseClick(const CEGUI::EventArgs& args);
		bool menuMainOptions_MouseClick(const CEGUI::EventArgs& args);
		bool menuMainQuit_MouseClick(const CEGUI::EventArgs& args);

		bool menuStartGameStart_MouseClick(const CEGUI::EventArgs& args);

		bool menuJoinGameJoin_MouseClick(const CEGUI::EventArgs& args);

	public:

		Menu();

		void init();

		void toggleVisible();
};

//------------------------------------------------------------------------------
