#include <Ogre.h>

#include "Fighter.h"
#include "MainState.h"

const float Fighter::MAX_SPEED = 500;
const float Fighter::MAX_FUELL = 10;
const float Fighter::ACCELERATION_SPEED = 100;
const float Fighter::ROTATION_SPEED = 0.2f;
const float Fighter::ROLL_SPEED = 3;
const float Fighter::CLIMB_SPEED = 1;
const float Fighter::BOOST_SPEED = 2;
const float Fighter::FUELL_SPEED = 0.4f;
const float Fighter::BOOST_FUELL = 1.0f;
const float Fighter::MAX_BOOST_SPEED = 1000;
const float Fighter::MIN_BOOST_FUELL = 0.4f;
const float Fighter::BOOST_DRAG = 100;

Fighter::Fighter(MainState& state) :
	m_state(state),
	m_speed(0),
	m_fuell(MAX_FUELL),
	m_boost(false)
{
	/* Fighter */
	m_fighter = state.getSceneManager()->createEntity("F14_mesh.mesh");
	m_fighter->setCastShadows(true);
	m_node = state.getSceneManager()->getRootSceneNode()->createChildSceneNode("FighterNode");
	m_node->attachObject(m_fighter);
	m_node->yaw(Ogre::Radian(-M_PI/2));
}

Fighter::~Fighter()
{
}

void Fighter::update(float time)
{
	if(m_boost)
	{
		float fuell = time * BOOST_FUELL;
		if(fuell > m_fuell)
			m_speed += m_fuell/fuell * time * BOOST_SPEED * ACCELERATION_SPEED;
		else
			m_speed += time * BOOST_SPEED * ACCELERATION_SPEED;
		m_fuell -= fuell;
		if(m_fuell <= 0)
		{
			m_fuell = 0;
			m_boost = false;
		}
		if(m_speed > MAX_BOOST_SPEED)
			m_speed = MAX_BOOST_SPEED;
	}
	else
	{
		m_fuell += time * FUELL_SPEED;
		if(m_fuell > MAX_FUELL)
			m_fuell = MAX_FUELL;
		if(m_speed > MAX_SPEED)
		{
			m_speed -= time * BOOST_DRAG;
			if(m_speed < MAX_SPEED)
				m_speed = MAX_SPEED;
		}
	}

	m_node->translate(0, 0, m_speed * time, Ogre::Node::TS_LOCAL);
}

void Fighter::roll(float angle)
{
	m_node->rotate(Ogre::Vector3::UNIT_Z, Ogre::Radian(angle * ROLL_SPEED));
}

void Fighter::rotate(float angle)
{
	m_node->rotate(Ogre::Vector3::UNIT_Y, Ogre::Radian(angle * ROLL_SPEED));
}

void Fighter::accelerate(float speed)
{
	if(m_speed > MAX_SPEED)
		return;

	m_speed += speed * ACCELERATION_SPEED;

	if(m_speed < 0)
		m_speed = 0;
	else if(m_boost)
	{
		if(m_speed > MAX_BOOST_SPEED)
			m_speed = MAX_BOOST_SPEED;
	}
	else if(m_speed > MAX_SPEED)
		m_speed = MAX_SPEED;
}

void Fighter::climb(float pitch)
{
	m_node->rotate(Ogre::Vector3::UNIT_X, Ogre::Radian(pitch * ROLL_SPEED));
}

const Ogre::Vector3& Fighter::getPosition()
{
	return m_node->getPosition();
}

Ogre::SceneNode * Fighter::getNode()
{
	return m_node;
}

void Fighter::boost(bool enabled)
{
	if(!enabled || m_fuell >= MIN_BOOST_FUELL)
		m_boost = enabled;
}

float Fighter::getFuell() const
{
	return m_fuell;
}

float Fighter::getSpeed() const
{
	return m_speed;
}

