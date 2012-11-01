#ifndef SDLKEYBOARD_H
#define SDLKEYBOARD_H

#include <SDL_events.h>

#include "InputDevice.h"

class SDLKeyboard : public InputDevice
{
public:
	SDLKeyboard();
	virtual ~SDLKeyboard();

	void process(SDL_Event& event, float time);

	virtual int translate(std::string name);
	virtual void process(float time);
};

#endif // SDLKEYBOARD_H
