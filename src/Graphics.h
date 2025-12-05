
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Tank2007.h"

//------------------------------------------------------------------------------

class Graphics : public Ogre::Singleton<Graphics>, public Ogre::FrameListener
{
	private:

		Ogre::Camera*			m_camera;
		Ogre::RenderWindow*		m_renderWindow;
		Ogre::Root*				m_root;
		Ogre::SceneManager*		m_sceneManager;
		Ogre::Viewport*			m_viewport;

		HWND					m_hWnd;
		bool					m_run;
		bool					m_key[256];
		bool					m_mouseButton[3];
		Ogre::Vector2			m_mouse2d;
		Ogre::Vector2			m_mouse2dOld;

		virtual bool frameStarted(const Ogre::FrameEvent& evt);

	public:

		Graphics();

		~Graphics();

		bool init();

		void run();

		Ogre::RenderWindow* getRenderWindow()
		{
			return m_renderWindow;
		}

		Ogre::SceneManager* getSceneManager()
		{
			return m_sceneManager;
		}

		void onClose();
		void onKeyDown(BYTE key);
		void onKeyUp(BYTE key);
		void onKeyDown2(BYTE key);
		void onKeyUp2(BYTE key);
		void onMouseButtonDown(BYTE button);
		void onMouseButtonUp(BYTE button);
		void onMouseMove(WORD x, WORD y);

		friend LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:

		DWORD m_dataCounter;

	public:

		WORD getDataCounter()
		{
			return m_dataCounter++;
		}

		std::string getDataCounterStr()
		{
			char getDataCounterStr[8];

			sprintf(getDataCounterStr, "%i", m_dataCounter++);

			return getDataCounterStr;
		}

	public:

		Ogre::Entity* createEntity(const std::string& meshName)
		{
			return m_sceneManager->createEntity(getDataCounterStr(), meshName);
		}

		Ogre::Entity* createEntity(const std::string& name, const std::string& meshName)
		{
			return m_sceneManager->createEntity(name, meshName);
		}

		Ogre::ManualObject* createManualObject()
		{
			return m_sceneManager->createManualObject(getDataCounterStr());
		}

		Ogre::ParticleSystem* createParticleSystem(std::string templateName)
		{
			return m_sceneManager->createParticleSystem(getDataCounterStr(), templateName);
		}

		Ogre::SceneNode* createSceneNode()
		{
			return m_sceneManager->getRootSceneNode()->createChildSceneNode(getDataCounterStr());
		}

		Ogre::SceneNode* createSceneNode(const std::string& name)
		{
			return m_sceneManager->getRootSceneNode()->createChildSceneNode(name);
		}

		void destroyEntity(Ogre::Entity* entity)
		{
			if (entity)

				m_sceneManager->destroyEntity(entity);
		}

		void destroyManualObject(Ogre::ManualObject* manualObject)
		{
			if (manualObject)

				m_sceneManager->destroyManualObject(manualObject);
		}

		void destroyParticleSystem(Ogre::ParticleSystem* particleSystem)
		{
			if (particleSystem)

				m_sceneManager->destroyParticleSystem(particleSystem);
		}

		void destroySceneNode(Ogre::SceneNode* sceneNode)
		{
			if (sceneNode)

				m_sceneManager->destroySceneNode(sceneNode->getName());
		}
};

//------------------------------------------------------------------------------
