
//------------------------------------------------------------------------------

#include "Tank2007.h"

#include "Console.h"
#include "Graphics.h"
#include "Gui.h"
#include "Menu.h"
#include "Multiplayer.h"
#include "ObjectManager.h"
#include "PlayerManager.h"

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
