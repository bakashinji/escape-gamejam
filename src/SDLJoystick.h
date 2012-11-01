#ifndef SDLJOYSTICK_H
#define SDLJOYSTICK_H

#include <SDL_events.h>

#include "InputDevice.h"

class SDLJoystick : public InputDevice
{
private:
	enum JoystickID
	{
		AXIS=0,
		BALLX=16,
		BALLY=32,
		HAT=48,
		BUTTON=64
	};

	SDL_Joystick* m_joystick;

public:
	SDLJoystick(int id);
	virtual ~SDLJoystick();

	void process(SDL_Event& event, float time);

	virtual int translate(std::string name);
	virtual void process(float time);
};

#endif // SDLJOYSTICK_H
