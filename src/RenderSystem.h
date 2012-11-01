#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SDL.h>

#include "GameSystem.h"

namespace Ogre
{
class Root;
class RenderWindow;
}

class RenderSystem : public GameSystem
{
private:
	SDL_Surface* m_screen;
	Ogre::Root* m_root;
	Ogre::RenderWindow* m_renderWindow;
public:
	RenderSystem(GameApplication& ga);
	virtual ~RenderSystem();

	Ogre::Root* getRoot() const;
	Ogre::RenderWindow* getRenderWindow() const;

	virtual void update(float time);
};

#endif // RENDERSYSTEM_H
