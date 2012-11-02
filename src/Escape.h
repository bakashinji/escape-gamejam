#ifndef WINGSOFCONCEPT_H
#define WINGSOFCONCEPT_H

#include <memory>
#include <OgreLogManager.h>

#include "GameApplication.h"
#include "RenderSystem.h"
#include "InputSystem.h"

class Escape : public GameApplication
{
private:
	Ogre::LogManager m_logger;

	std::unique_ptr<RenderSystem> m_renderer;
	std::unique_ptr<InputSystem> m_input;

public:
	Escape();

	RenderSystem& getRenderSystem();
	InputSystem& getInputSystem();

	virtual void init();
	virtual void exit();
	virtual void update(float time);
};

#endif // WINGSOFCONCEPT_H
