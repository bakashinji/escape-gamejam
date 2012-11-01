#ifndef FIGHTER_H
#define FIGHTER_H

#include "GameObject.h"

namespace Ogre
{
	class Entity;
	class SceneNode;
	class Vector3;
}

class MainState;

class Fighter : public GameObject
{
private:
	MainState& m_state;
	Ogre::Entity* m_fighter;
	Ogre::SceneNode* m_node;

	float m_speed;
	float m_fuell;
	bool m_boost;

public:
	static const float MAX_SPEED;
	static const float MAX_FUELL;
	static const float ACCELERATION_SPEED;
	static const float ROTATION_SPEED;
	static const float ROLL_SPEED;
	static const float CLIMB_SPEED;
	static const float BOOST_SPEED;
	static const float FUELL_SPEED;
	static const float BOOST_FUELL;
	static const float MAX_BOOST_SPEED;
	static const float MIN_BOOST_FUELL;
	static const float BOOST_DRAG;

	Fighter(MainState& state);
	virtual ~Fighter();

	const Ogre::Vector3& getPosition();
	Ogre::SceneNode* getNode();

	float getSpeed() const;
	float getFuell() const;

	void update(float time);

	void roll(float angle);
	void rotate(float angle);
	void accelerate(float speed);
	void climb(float pitch);
	void boost(bool enabled);
};

#endif // FIGHTER_H
