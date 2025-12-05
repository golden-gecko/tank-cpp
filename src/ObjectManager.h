
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Tank2007.h"

#include "ResourceManager.h"
#include "Tank.h"
#include "Wall.h"

//------------------------------------------------------------------------------

class ObjectManager : public ResourceManager<Object>, public Ogre::Singleton<ObjectManager>
{
	public:

		void destroy(Object* object);

		void update(float deltaTime);
};

//------------------------------------------------------------------------------
