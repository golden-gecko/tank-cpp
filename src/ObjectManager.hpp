
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Tank2007.hpp"

#include "ResourceManager.hpp"
#include "Tank.hpp"
#include "Wall.hpp"

//------------------------------------------------------------------------------

class ObjectManager : public ResourceManager<Object>, public Ogre::Singleton<ObjectManager>
{
	public:

		void destroy(Object* object);

		void update(float deltaTime);
};

//------------------------------------------------------------------------------
