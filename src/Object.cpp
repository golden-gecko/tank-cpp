
//------------------------------------------------------------------------------

#include "Tank2007.hpp"

#include "Object.hpp"

#include "Graphics.hpp"

//------------------------------------------------------------------------------

Object::Object()
	:	m_sceneNode(Graphics::getSingletonPtr()->createSceneNode()),
		m_linearDamping(Ogre::Vector3::ZERO),
		m_linearVelocity(Ogre::Vector3::ZERO)
{
}

//------------------------------------------------------------------------------

Object::~Object()
{
	Graphics::getSingletonPtr()->destroySceneNode(m_sceneNode);
}

//------------------------------------------------------------------------------

Ogre::Vector3 Object::getDirection()
{
	return m_sceneNode->getOrientation().zAxis() * -1.0f;
}

//------------------------------------------------------------------------------

Ogre::Vector3 Object::getLinearDamping()
{
	return m_linearDamping;
}

//------------------------------------------------------------------------------

Ogre::Vector3 Object::getLinearVelocity()
{
	return m_linearVelocity;
}

//------------------------------------------------------------------------------

Ogre::Vector3 Object::getPosition()
{
	return m_sceneNode->getPosition();
}

//------------------------------------------------------------------------------

void Object::setDirection(float x, float y, float z)
{
	setDirection(Ogre::Vector3(x, y, z));
}

//------------------------------------------------------------------------------

void Object::setDirection(const Ogre::Vector3& v)
{
	m_sceneNode->setDirection(v);
}

//------------------------------------------------------------------------------

void Object::setLinearDamping(float x, float y, float z)
{
	setLinearVelocity(Ogre::Vector3(x, y, z));
}

//------------------------------------------------------------------------------

void Object::setLinearDamping(const Ogre::Vector3& v)
{
	m_linearDamping = v;
}

//------------------------------------------------------------------------------

void Object::setLinearVelocity(float x, float y, float z)
{
	setLinearVelocity(Ogre::Vector3(x, y, z));
}

//------------------------------------------------------------------------------

void Object::setLinearVelocity(const Ogre::Vector3& v)
{
	m_linearVelocity = v;
}

//------------------------------------------------------------------------------

void Object::setPosition(float x, float y, float z)
{
	setPosition(Ogre::Vector3(x, y, z));
}

//------------------------------------------------------------------------------

void Object::setPosition(const Ogre::Vector3& v)
{
	m_sceneNode->setPosition(v);
}

//------------------------------------------------------------------------------

bool Object::update(float deltaTime)
{
	if (m_linearVelocity.x != 0.0f)

		m_linearVelocity.x -=
			m_linearDamping.x *
			(m_linearVelocity.x /
			fabs(m_linearVelocity.x)) *
			deltaTime;

	if (m_linearVelocity.y != 0.0f)

		m_linearVelocity.y -=
			m_linearDamping.y *
			(m_linearVelocity.y /
			fabs(m_linearVelocity.y)) *
			deltaTime;

	if (m_linearVelocity.z != 0.0f)

		m_linearVelocity.z -=
			m_linearDamping.z *
			(m_linearVelocity.z /
			fabs(m_linearVelocity.z)) *
			deltaTime;

	//

	if (m_linearVelocity.length() < 0.05f)

		m_linearVelocity = Ogre::Vector3::ZERO;

	//

	m_sceneNode->translate(m_linearVelocity * deltaTime);

	//

    return true;
}

//------------------------------------------------------------------------------
