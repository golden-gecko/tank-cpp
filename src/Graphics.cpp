
//------------------------------------------------------------------------------

#include "Tank2007.hpp"

#include "Graphics.hpp"

#include "Console.hpp"
#include "Gui.hpp"
#include "Menu.hpp"
#include "Multiplayer.hpp"
#include "ObjectManager.hpp"

//------------------------------------------------------------------------------

Graphics::Graphics() :
	m_camera(NULL),
	m_renderWindow(NULL),
	m_root(NULL),
	m_sceneManager(NULL),
	m_viewport(NULL),
	m_hWnd(NULL),
	m_run(true),
	m_mouse2d(Ogre::Vector2::ZERO),
	m_mouse2dOld(Ogre::Vector2::ZERO)
{
	memset(m_key, false, 256);
	memset(m_mouseButton, false, 3);

//	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
}

//------------------------------------------------------------------------------

Graphics::~Graphics()
{
	ShowCursor(TRUE);

	if (m_root)

		delete m_root;
}

//------------------------------------------------------------------------------

bool Graphics::init()
{
	// Root

	m_root = new Ogre::Root("Plugins.cfg", "Ogre.cfg", "Ogre.log");
	m_root->addFrameListener(this);

	// Resources

	Ogre::ConfigFile cf;

	cf.load("Resources.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	std::string secName, typeName, archName;

	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();

		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i) {

			typeName = i->first;
			archName = i->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}

	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

	// Render System

	Ogre::RenderSystemList* renderSystemList = m_root->getAvailableRenderers();

	for (Ogre::RenderSystemList::iterator i = renderSystemList->begin(); i != renderSystemList->end(); i++)
	{
		if ((*i)->getName() == "Direct3D9 Rendering Subsystem")
		{
			m_root->setRenderSystem((*i));

			break;
		}
	}

	m_root->initialise(false);

	// External Render Window

	WNDCLASS wc;

	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= WindowProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= (HINSTANCE)GetModuleHandle(NULL);
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "OpenGL";

	if (!RegisterClass(&wc))

		return false;

	m_hWnd = CreateWindow(
		"OpenGL", "OpenGL",
//		WS_VISIBLE | WS_POPUP,
		WS_VISIBLE | WS_OVERLAPPEDWINDOW,
//		0, 0, 1280, 1024,
		0, 0, 1024, 768,
		NULL, NULL, (HINSTANCE)GetModuleHandle(NULL), NULL);

	if (m_hWnd == NULL)

		return false;

	SetForegroundWindow(m_hWnd);

	Ogre::NameValuePairList miscParams;

    miscParams.insert(
        Ogre::NameValuePairList::value_type("externalWindowHandle",
        Ogre::StringConverter::toString((long)m_hWnd))); 

	m_renderWindow = m_root->createRenderWindow("WarGAME p r o j e c t", 1280, 1024, false, &miscParams);
	m_mouse2d.x = m_mouse2dOld.x = m_renderWindow->getWidth() / 2;
	m_mouse2d.y = m_mouse2dOld.y = m_renderWindow->getHeight() / 2;
	ShowCursor(FALSE);

	// Scene Manager

	m_sceneManager = m_root->createSceneManager(Ogre::ST_EXTERIOR_CLOSE, "MainSceneManager");
	m_sceneManager->setShadowFarDistance(512.0f);
	m_sceneManager->setShadowUseInfiniteFarPlane(false);

	// Camera

	m_camera = m_sceneManager->createCamera("MainCamera");
	m_camera->setPosition(10, 21, 20);
	m_camera->lookAt(10, 0, 11);
	m_camera->setNearClipDistance(0.5f);
	m_camera->setFarClipDistance(512.0f);

	// Viewport

	m_viewport = m_renderWindow->addViewport(m_camera);
	m_viewport->setBackgroundColour(Ogre::ColourValue(0.0f, 0.5f, 0.75f));

	m_camera->setAspectRatio(
		Ogre::Real(m_viewport->getActualWidth()) / Ogre::Real(m_viewport->getActualHeight()));

	return true;
}

//------------------------------------------------------------------------------

Ogre::Entity* e;
Ogre::SceneNode* sn;

void Graphics::run()
{
	Ogre::Light* l00 = m_sceneManager->createLight("00");
	l00->setType(Ogre::Light::LT_POINT);
	l00->setPosition(10, 20, 10);
	l00->setDiffuseColour(0.75, 0.75, 0.75);

	/*
	Ogre::Light* l0 = m_sceneManager->createLight("0");
	l0->setType(Ogre::Light::LT_SPOTLIGHT);
	l0->setPosition(0, 10, 0);
	l0->setDirection(0.6, -1, 0.6);
	l0->setDiffuseColour(0.25, 0.25, 0.25);
	l0->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(45)));
	l0->setCastShadows(false);

	Ogre::Light* l1 = m_sceneManager->createLight("1");
	l1->setType(Ogre::Light::LT_SPOTLIGHT);
	l1->setPosition(20, 10, 0);
	l1->setDirection(-0.6, -1, 0.6);
	l1->setDiffuseColour(0.25, 0.25, 0.25);
	l1->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(45)));
	l1->setCastShadows(false);

	Ogre::Light* l2 = m_sceneManager->createLight("2");
	l2->setType(Ogre::Light::LT_SPOTLIGHT);
	l2->setPosition(20, 10, 20);
	l2->setDirection(-0.6, -1, -0.6);
	l2->setDiffuseColour(0.25, 0.25, 0.25);
	l2->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(45)));
	l2->setCastShadows(false);

	Ogre::Light* l3 = m_sceneManager->createLight("3");
	l3->setType(Ogre::Light::LT_SPOTLIGHT);
	l3->setPosition(0, 10, 20);
	l3->setDirection(0.6, -1, -0.6);
	l3->setDiffuseColour(0.25, 0.25, 0.25);
	l3->setSpotlightOuterAngle(Ogre::Radian(Ogre::Degree(45)));
	l3->setCastShadows(false);
	//*/

	//*
	{
		Ogre::Entity* e = createEntity("plane.mesh");
		e->setCastShadows(false);
		Ogre::SceneNode* sn = createSceneNode();
		sn->attachObject(e);
		sn->setScale(20, 20, 20);
		sn->setDirection(1, 0, 0);
		sn->setPosition(Ogre::Vector3(0, 10, 10));
	}
	{
		Ogre::Entity* e = createEntity("plane.mesh");
		e->setCastShadows(false);
		Ogre::SceneNode* sn = createSceneNode();
		sn->attachObject(e);
		sn->setScale(20, 20, 20);
		sn->setDirection(0, 1, 0);
		sn->setPosition(Ogre::Vector3(10, 0, 10));
	}
	{
		Ogre::Entity* e = createEntity("plane.mesh");
		e->setCastShadows(false);
		Ogre::SceneNode* sn = createSceneNode();
		sn->attachObject(e);
		sn->setScale(20, 20, 20);
		sn->setDirection(0, 0, 1);
		sn->setPosition(Ogre::Vector3(10, 10, 0));
	}

	{
		Ogre::Entity* e = createEntity("plane.mesh");
		e->setCastShadows(false);
		Ogre::SceneNode* sn = createSceneNode();
		sn->attachObject(e);
		sn->setScale(20, 20, 20);
		sn->setDirection(-1, 0, 0);
		sn->setPosition(Ogre::Vector3(20, 10, 10));
	}
	{
		Ogre::Entity* e = createEntity("plane.mesh");
		e->setCastShadows(false);
		Ogre::SceneNode* sn = createSceneNode();
		sn->attachObject(e);
		sn->setScale(20, 20, 20);
		sn->setDirection(0, -1, 0);
		sn->setPosition(Ogre::Vector3(10, 20, 10));
	}
	{
		Ogre::Entity* e = createEntity("plane.mesh");
		e->setCastShadows(false);
		Ogre::SceneNode* sn = createSceneNode();
		sn->attachObject(e);
		sn->setScale(20, 20, 20);
		sn->setDirection(0, 0, -1);
		sn->setPosition(Ogre::Vector3(10, 10, 20));
	}
	//*/

	for (int z = 0; z < 20; z++)
	{
		for (int x = 0; x < 20; x++)
		{
			if (z == 0 || z == 19 || x == 0 || x == 19)
			{
				e = createEntity("wall_steel.mesh");
				sn = createSceneNode();
				sn->attachObject(e);
				sn->setPosition(Ogre::Vector3(0.5 + x, 0, 0.5 + z));
			}
		}
	}

	/*
	for (int z = 0; z < 20; z++)
	{
		for (int x = 0; x < 20; x++)
		{
			if ((z != 0 && z != 19 && x != 0 && x != 19) && ((x - 9.5) * (x - 9.5) + (z - 9.5) * (z - 9.5) >= 4))
			{
				e = createEntity("wall_brick.mesh");
				sn = createSceneNode();
				sn->attachObject(e);
				sn->setPosition(Ogre::Vector3(0.5 + x, 0, 0.5 + z));
			}
		}
	}
	*/

	{
		e = createEntity("jaiqua.mesh");
		sn = createSceneNode();
		sn->attachObject(e);
		sn->setScale(2, 2, 2);
		sn->setPosition(Ogre::Vector3(10, 0, 10));
	}

	m_root->getRenderSystem()->_initRenderTargets();

	m_root->clearEventTimes();

	MSG msg;

	float time = 0.0f;
	LARGE_INTEGER f, current, last;

	QueryPerformanceFrequency(&f);
	QueryPerformanceCounter(&current);
	QueryPerformanceCounter(&last);

	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		/*
		time += ((float)last.QuadPart - (float)current.QuadPart) / (float)f.QuadPart;
		current = last;

		QueryPerformanceCounter(&last);

		if (time >= 32.0f / 1000.0f)
		{
			time = 0.0f;
		//*/

			m_root->renderOneFrame();
		//}
	}
	while (m_run);
}

//------------------------------------------------------------------------------

bool Graphics::frameStarted(const Ogre::FrameEvent& evt)
{
	ObjectManager::getSingletonPtr()->update(evt.timeSinceLastFrame);

	//

	if (m_key[VK_ESCAPE])

		onClose();

	//

	if (m_key[VK_UP])

		m_camera->moveRelative(Ogre::Vector3(0, 0, -15 * evt.timeSinceLastFrame));

	if (m_key[VK_DOWN])

		m_camera->moveRelative(Ogre::Vector3(0, 0,  15 * evt.timeSinceLastFrame));

	if (m_key[VK_LEFT])

		m_camera->moveRelative(Ogre::Vector3(-15 * evt.timeSinceLastFrame, 0, 0));

	if (m_key[VK_RIGHT])

		m_camera->moveRelative(Ogre::Vector3( 15 * evt.timeSinceLastFrame, 0, 0));

	//

	if (m_key['W'])

		sn->translate(sn->getOrientation().zAxis() * -5 * evt.timeSinceLastFrame);

	if (m_key['S'])

		sn->translate(sn->getOrientation().zAxis() *  5 * evt.timeSinceLastFrame);

	if (m_key['A'])

		sn->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree( 75 * evt.timeSinceLastFrame)));

	if (m_key['D'])

		sn->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(Ogre::Degree(-75 * evt.timeSinceLastFrame)));

	return m_run;
}

//------------------------------------------------------------------------------

void Graphics::onClose()
{
	m_run = false;
}

//------------------------------------------------------------------------------
void Graphics::onKeyDown2(BYTE key)
{
	m_key[key] = true;

}
void Graphics::onKeyDown(BYTE key)
{
	if (m_key[key] == false)
	{
		Multiplayer::getSingletonPtr()->onKeyDown(key);

		m_key[key] = true;
	}

	switch (key)
	{
		case VK_F1:

			Menu::getSingletonPtr()->toggleVisible();

			return;

		case VK_F5:

			Console::getSingletonPtr()->toggleVisible();

			return;

		case VK_F9:

			if (m_sceneManager->getShadowTechnique() != Ogre::SHADOWTYPE_NONE)

				m_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE);

			else

				m_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

			return;
	}
}

//------------------------------------------------------------------------------
void Graphics::onKeyUp2(BYTE key)
{
	m_key[key] = false;
}
void Graphics::onKeyUp(BYTE key)
{
	Multiplayer::getSingletonPtr()->onKeyUp(key);

	m_key[key] = false;
}

//------------------------------------------------------------------------------

void Graphics::onMouseButtonDown(BYTE button)
{
	m_mouseButton[button] = true;

	// Update CEGUI.

	CEGUI::System::getSingletonPtr()->injectMouseButtonDown(
		CEGUI::MouseButton(button));
}

//------------------------------------------------------------------------------

void Graphics::onMouseButtonUp(BYTE button)
{
	m_mouseButton[button] = false;

	// Update CEGUI.

	CEGUI::System::getSingletonPtr()->injectMouseButtonUp(
		CEGUI::MouseButton(button));
}

//------------------------------------------------------------------------------

void Graphics::onMouseMove(WORD x, WORD y)
{
	m_mouse2d.x = x;
	m_mouse2d.y = y;

	if (m_mouseButton[CEGUI::MiddleButton])
	{
		m_camera->yaw(
			Ogre::Degree((m_mouse2dOld.x - x) * 0.15f));
		m_camera->pitch(
			Ogre::Degree((m_mouse2dOld.y - y) * 0.15f));
	}

	// Update CEGUI.

	CEGUI::System::getSingletonPtr()->injectMouseMove(
		x - m_mouse2dOld.x, y - m_mouse2dOld.y);

	//

	m_mouse2dOld.x = x;
	m_mouse2dOld.y = y;
}

//------------------------------------------------------------------------------

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static float speed = 15.0f;

	switch (uMsg)
	{
		case WM_DESTROY:
			Graphics::getSingletonPtr()->onClose();
			return 0;

		case WM_KEYDOWN:
			Graphics::getSingletonPtr()->onKeyDown((BYTE)wParam);
			return 0;

		case WM_KEYUP:
			Graphics::getSingletonPtr()->onKeyUp((BYTE)wParam);
			return 0;

		case WM_LBUTTONDOWN:
			Graphics::getSingletonPtr()->onMouseButtonDown(0);
			return 0;

		case WM_LBUTTONUP:
			Graphics::getSingletonPtr()->onMouseButtonUp(0);
			return 0;

		case WM_MBUTTONDOWN:
			Graphics::getSingletonPtr()->onMouseButtonDown(2);
			return 0;

		case WM_MBUTTONUP:
			Graphics::getSingletonPtr()->onMouseButtonUp(2);
			return 0;

		case WM_MOUSEMOVE:
			Graphics::getSingletonPtr()->onMouseMove(LOWORD(lParam), HIWORD(lParam));
			return 0;

		case WM_RBUTTONDOWN:
			Graphics::getSingletonPtr()->onMouseButtonDown(1);
			return 0;

		case WM_RBUTTONUP:
			Graphics::getSingletonPtr()->onMouseButtonUp(1);
			return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//------------------------------------------------------------------------------
