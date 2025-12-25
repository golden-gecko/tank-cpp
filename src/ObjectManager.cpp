
//------------------------------------------------------------------------------

#include "Tank2007.hpp"

#include "ObjectManager.hpp"

//------------------------------------------------------------------------------

void ObjectManager::destroy(Object* object)
{
	ResourceManager::destroy(object);
}

//------------------------------------------------------------------------------

void ObjectManager::update(float deltaTime)
{
	for (std::list<Object*>::iterator itr = mList.begin(); itr != mList.end(); itr++)

		(*itr)->update(deltaTime);
}

//------------------------------------------------------------------------------
