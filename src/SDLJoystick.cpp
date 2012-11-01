#include "SDLJoystick.h"
#include "MessageException.h"

SDLJoystick::SDLJoystick(int id)
{
	m_joystick = SDL_JoystickOpen(id);
	if(!m_joystick)
		throw MessageException(SDL_GetError(), MessageExceptionType::WARNING);
}

SDLJoystick::~SDLJoystick()
{
	SDL_JoystickClose(m_joystick);
}

void SDLJoystick::process(SDL_Event &event, float time)
{
	switch(event.type)
	{
	case SDL_JOYAXISMOTION:
		fire(AXIS + event.jaxis.axis, event.jaxis.value / 32768.0f, time);
		break;
	case SDL_JOYBALLMOTION:
		fire(BALLX + event.jball.ball, event.jball.xrel / 32768.0f, time);
		fire(BALLY + event.jball.ball, event.jball.yrel / 32768.0f, time);
		break;
	case SDL_JOYHATMOTION:
		fire(HAT + event.jhat.hat, event.jhat.value, time);
		break;
	case SDL_JOYBUTTONDOWN:
		fire(BUTTON + event.jbutton.button, 1, time);
		break;
	case SDL_JOYBUTTONUP:
		fire(BUTTON + event.jbutton.button, 0, time);
		break;
	}
}

int SDLJoystick::translate(std::string name)
{
	int id;

	id = nameToID(name, "axis");

	if(id > 0 && id <= 32)
		return AXIS + id - 1;

	id = nameToID(name, "ballx");

	if(id > 0 && id <= 32)
		return BALLX + id - 1;

	id = nameToID(name, "bally");

	if(id > 0 && id <= 32)
		return BALLY + id - 1;

	id = nameToID(name, "hat");

	if(id > 0 && id <= 32)
		return HAT + id - 1;

	id = nameToID(name, "button");

	if(id > 0 && id <= 128)
		return BUTTON + id - 1;

	return NOT_FOUND;
}

void SDLJoystick::process(float time)
{
	for(auto& button : m_continuous)
	{
		if(button.first >= AXIS && button.first < AXIS + 32)
		{
			button.second->execute(SDL_JoystickGetAxis(m_joystick, button.first - AXIS) / 32768.0f, time);
		}
		else if(button.first >= BALLX && button.first < BALLY + 32)
		{
			int x, y;
			SDL_JoystickGetBall(m_joystick, button.first % 32, &x, &y);
			if(button.first < BALLY)
				button.second->execute(x / 32768.0f, time);
			else
				button.second->execute(y / 32768.0f, time);
		}
		else if(button.first >= HAT && button.first < HAT + 32)
		{
			button.second->execute(SDL_JoystickGetHat(m_joystick, button.first - HAT), time);
		}
		else if(button.first >= BUTTON && button.first < BUTTON + 128)
		{
			button.second->execute(SDL_JoystickGetButton(m_joystick, button.first - BUTTON), time);
		}
	}
}
