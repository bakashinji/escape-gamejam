#ifndef SDLMOUSE_H
#define SDLMOUSE_H

#include <SDL_events.h>

#include "InputDevice.h"

class SDLMouse : public InputDevice
{
private:
	enum MouseID
	{
		BUTTON1,
		BUTTON2,
		BUTTON3,
		BUTTON4,
		BUTTON5,
		BUTTON6,
		BUTTON7,
		BUTTON8,
		RELX,
		RELY
	};

	int m_width;
	int m_height;

public:
	SDLMouse(int width, int height);
	virtual ~SDLMouse();

	void process(SDL_Event& event, float time);

	virtual int translate(std::string name);
	virtual void process(float time);
};

#endif // SDLMOUSE_H
