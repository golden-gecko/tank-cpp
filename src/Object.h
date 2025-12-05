
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Tank2007.h"

#include "Resource.h"

//------------------------------------------------------------------------------

class Object : public Resource
{
	protected:

		Ogre::SceneNode*	m_sceneNode;

		Ogre::Vector3		m_linearDamping;
		Ogre::Vector3		m_linearVelocity;

	public:

		 Object();
		~Object();

		Ogre::Vector3 getDirection();
		Ogre::Vector3 getLinearAcceleration();
		Ogre::Vector3 getLinearDamping();
		Ogre::Vector3 getLinearVelocity();
		Ogre::Vector3 getPosition();

		void setDirection(float x, float y, float z);
		void setDirection(const Ogre::Vector3& v);

		void setLinearAcceleration(float x, float y, float z);
		void setLinearAcceleration(const Ogre::Vector3& v);

		void setLinearDamping(float x, float y, float z);
		void setLinearDamping(const Ogre::Vector3& v);

		void setLinearVelocity(float x, float y, float z);
		void setLinearVelocity(const Ogre::Vector3& v);

		void setPosition(float x, float y, float z);
		void setPosition(const Ogre::Vector3& v);

		virtual bool update(float deltaTime);
};

//------------------------------------------------------------------------------
