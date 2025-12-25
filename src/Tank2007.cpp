
//------------------------------------------------------------------------------

#include "Tank2007.hpp"

#include "Console.hpp"
#include "Graphics.hpp"
#include "Gui.hpp"
#include "Menu.hpp"
#include "Multiplayer.hpp"
#include "ObjectManager.hpp"
#include "PlayerManager.hpp"

Console			console;
Graphics		graphics;
Gui				gui;
Menu			menu;
Multiplayer		multiplayer;
ObjectManager	objectManager;
PlayerManager	playerManager;

//------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if (graphics.init() && gui.init()) {

		console.init();
		menu.init();

		graphics.run();
	}

	return 0;
}

//------------------------------------------------------------------------------
