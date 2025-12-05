
//------------------------------------------------------------------------------

#include "Tank2007.h"

#include "Menu.h"

#include "Multiplayer.h"

//------------------------------------------------------------------------------

bool Menu::menuMainStartGame_MouseClick(const CEGUI::EventArgs& args)
{
	mMenuStartGame->setVisible(true);
	mMenuJoinGame->setVisible(false);
	mMenuOptions->setVisible(false);

	return true;
}

//------------------------------------------------------------------------------

bool Menu::menuMainJoinGame_MouseClick(const CEGUI::EventArgs& args)
{
	mMenuStartGame->setVisible(false);
	mMenuJoinGame->setVisible(true);
	mMenuOptions->setVisible(false);

	return true;
}

//------------------------------------------------------------------------------

bool Menu::menuMainReturnToGame_MouseClick(const CEGUI::EventArgs& args)
{
	return true;
}

//------------------------------------------------------------------------------

bool Menu::menuMainOptions_MouseClick(const CEGUI::EventArgs& args)
{
	mMenuStartGame->setVisible(false);
	mMenuJoinGame->setVisible(false);
	mMenuOptions->setVisible(true);

	return true;
}

//------------------------------------------------------------------------------

bool Menu::menuMainQuit_MouseClick(const CEGUI::EventArgs& args)
{
	return true;
}

//------------------------------------------------------------------------------

bool Menu::menuStartGameStart_MouseClick(const CEGUI::EventArgs& args)
{
	mMenuMain->setVisible(false);
	mMenuStartGame->setVisible(false);

	Multiplayer::getSingletonPtr()->startGame();

	return true;
}

//------------------------------------------------------------------------------

bool Menu::menuJoinGameJoin_MouseClick(const CEGUI::EventArgs& args)
{
	mMenuMain->setVisible(false);
	mMenuJoinGame->setVisible(false);

	Multiplayer::getSingletonPtr()->joinGame("127.0.0.1");

	return true;
}

//------------------------------------------------------------------------------

Menu::Menu() :
	mMenuMain(NULL),
	mMenuStartGame(NULL),
	mMenuJoinGame(NULL),
	mMenuOptions(NULL),
	mMenuMainStartGame(NULL),
	mMenuMainJoinGame(NULL),
	mMenuMainReturnToGame(NULL),
	mMenuMainOptions(NULL),
	mMenuMainQuit(NULL),
	mMenuStartGameStart(NULL)
{
}

//------------------------------------------------------------------------------

void Menu::init()
{
	mMenuMain = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Menu/Main");
	mMenuStartGame = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Menu/StartGame");
	mMenuJoinGame = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Menu/JoinGame");
	mMenuOptions = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Menu/Options");

	mMenuMainStartGame = (CEGUI::PushButton*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Menu/Main/StartGame");
	mMenuMainJoinGame = (CEGUI::PushButton*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Menu/Main/JoinGame");
	mMenuMainReturnToGame = (CEGUI::PushButton*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Menu/Main/ReturnToGame");
	mMenuMainOptions = (CEGUI::PushButton*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Menu/Main/Options");
	mMenuMainQuit = (CEGUI::PushButton*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Menu/Main/Quit");

	mMenuStartGameStart = (CEGUI::PushButton*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Menu/StartGame/Start");

	mMenuJoinGameJoin = (CEGUI::PushButton*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Menu/JoinGame/Join");

	mMenuMainStartGame->subscribeEvent(
		CEGUI::PushButton::EventMouseClick,
		CEGUI::Event::Subscriber(&Menu::menuMainStartGame_MouseClick, this));
	mMenuMainJoinGame->subscribeEvent(
		CEGUI::PushButton::EventMouseClick,
		CEGUI::Event::Subscriber(&Menu::menuMainJoinGame_MouseClick, this));
	mMenuMainReturnToGame->subscribeEvent(
		CEGUI::PushButton::EventMouseClick,
		CEGUI::Event::Subscriber(&Menu::menuMainReturnToGame_MouseClick, this));
	mMenuMainOptions->subscribeEvent(
		CEGUI::PushButton::EventMouseClick,
		CEGUI::Event::Subscriber(&Menu::menuMainOptions_MouseClick, this));
	mMenuMainQuit->subscribeEvent(
		CEGUI::PushButton::EventMouseClick,
		CEGUI::Event::Subscriber(&Menu::menuMainQuit_MouseClick, this));

	mMenuStartGameStart->subscribeEvent(
		CEGUI::PushButton::EventMouseClick,
		CEGUI::Event::Subscriber(&Menu::menuStartGameStart_MouseClick, this));

	mMenuJoinGameJoin->subscribeEvent(
		CEGUI::PushButton::EventMouseClick,
		CEGUI::Event::Subscriber(&Menu::menuJoinGameJoin_MouseClick, this));
}

//------------------------------------------------------------------------------

void Menu::toggleVisible()
{
	mMenuMain->setVisible(!mMenuMain->isVisible());
}

//------------------------------------------------------------------------------
