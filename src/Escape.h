#ifndef WINGSOFCONCEPT_H
#define WINGSOFCONCEPT_H

#include <memory>
#include <OgreLogManager.h>

#include "GameApplication.h"
#include "RenderSystem.h"
#include "InputSystem.h"

class TheEscape : public GameApplication
{
private:
	Ogre::LogManager m_logger;

	RenderSystem* m_renderer;
	InputSystem* m_input;

public:
	TheEscape();
	~TheEscape();

	RenderSystem& getRenderSystem();
	InputSystem& getInputSystem();

	virtual void init();
	virtual void exit();
	virtual void update(float time);
};

#endif // WINGSOFCONCEPT_H
