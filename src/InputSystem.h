#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <list>
#include <map>
#include <memory>
#include <SDL.h>
#include <boost/shared_ptr.hpp>

#include "GameSystem.h"
#include "SDLMouse.h"
#include "SDLKeyboard.h"
#include "SDLJoystick.h"
#include "unique_ptr.h"

class InputDevice;
class IConfiguration;



class InputSystem : public GameSystem
{
private:
	SDLMouse* m_mouse;
	SDLKeyboard* m_keyboard;
	std::map<int, boost::shared_ptr<SDLJoystick> > m_joysticks;

public:
	InputSystem(GameApplication& ga);
	virtual ~InputSystem();

	void bind(IConfiguration& config, std::vector<boost::shared_ptr<IInputAction> >& actions);
	void unBindAll();

	virtual void update(float time);
	void process(SDL_Event& event, float time);
};

#endif // INPUTSYSTEM_H
