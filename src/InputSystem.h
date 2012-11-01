#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <list>
#include <map>
#include <memory>
#include <SDL.h>

#include "GameSystem.h"
#include "SDLMouse.h"
#include "SDLKeyboard.h"
#include "SDLJoystick.h"

class InputDevice;
class IConfiguration;

class InputSystem : public GameSystem
{
private:
	std::unique_ptr<SDLMouse> m_mouse;
	std::unique_ptr<SDLKeyboard> m_keyboard;
	std::map<int, std::shared_ptr<SDLJoystick>> m_joysticks;

public:
	InputSystem(GameApplication& ga);
	virtual ~InputSystem();

	void bind(IConfiguration& config, std::vector<std::shared_ptr<IInputAction>>& actions);
	void unBindAll();

	virtual void update(float time);
	void process(SDL_Event& event, float time);
};

#endif // INPUTSYSTEM_H
