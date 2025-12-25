
//------------------------------------------------------------------------------

#include "Tank2007.hpp"

#include "Graphics.hpp"
#include "Gui.hpp"

//------------------------------------------------------------------------------

Gui::Gui() : mSystem(NULL), mRenderer(NULL)
{
}

//------------------------------------------------------------------------------

Gui::~Gui()
{
	if (mSystem)
		
		delete mSystem;

	if (mRenderer)
		
		delete mRenderer;
}

//------------------------------------------------------------------------------

bool Gui::init()
{
	// Setup Ogre CEGUI Renderer and CEGUI system.

	mRenderer = new CEGUI::OgreCEGUIRenderer(
		Graphics::getSingletonPtr()->getRenderWindow(),
		Ogre::RENDER_QUEUE_OVERLAY,
		false,
		3000,
		Graphics::getSingletonPtr()->getSceneManager());

	if (mRenderer)
	{
		mSystem = new CEGUI::System(mRenderer);

		if (mSystem)
		{
			// Load scheme, layout and setup defaults.

			CEGUI::SchemeManager::getSingletonPtr()->loadScheme(
				(CEGUI::utf8*)"TaharezLook.scheme");

			mSystem->setDefaultMouseCursor("TaharezLook", "MouseArrow");

			mSystem->setDefaultFont("BankGothicMediumBT");

			mSystem->setGUISheet(
				CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout(
					"Gui.xml"));

			//

			CEGUI::WindowManager::WindowIterator itr =
				CEGUI::WindowManager::getSingletonPtr()->getIterator();

			itr.toStart();

			while (itr.isAtEnd() == false)
			{
				itr.getCurrentValue()->setAlpha(0.75f);

				itr++;
			}

			return true;
		}
	}

	return false;
}

//------------------------------------------------------------------------------
