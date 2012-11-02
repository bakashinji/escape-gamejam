#include <SDL_mouse.h>

#include <boost/foreach.hpp>

#include "SDLMouse.h"

SDLMouse::SDLMouse(int width, int height) :
	m_width(width),
	m_height(height)
{
}

SDLMouse::~SDLMouse()
{
}

void SDLMouse::process(SDL_Event &event, float time)
{
	switch(event.type)
	{
	case SDL_MOUSEMOTION:
		fire(RELX, event.motion.xrel / float(m_width), time);
		fire(RELY, event.motion.yrel / float(m_height), time);
		break;
	case SDL_MOUSEBUTTONDOWN:
		fire(event.button.button - 1 + BUTTON1, 1, time);
		break;
	case SDL_MOUSEBUTTONUP:
		fire(event.button.button - 1 + BUTTON1, 0, time);
		break;
	}
}

int SDLMouse::translate(std::string name)
{
	int id;

	id = nameToID(name, "button");

	if(id > 0 && id <= 8)
		return BUTTON1 + id - 1;

	if(name == "relx")
		return RELX;

	if(name == "rely")
		return RELY;

	return NOT_FOUND;
}

void SDLMouse::process(float time)
{
	int x, y;
	Uint8 state = SDL_GetMouseState(&x, &y);
	//SDL_WarpMouse(m_width >> 1, m_height >> 1);

	x -= m_width >> 1;
	y -= m_height >> 1;

	typedef std::pair<const int, boost::shared_ptr<IInputAction> > temp;
	BOOST_FOREACH(temp& button, m_continuous)
	{
		if(button.first >= BUTTON1 && button.first <= BUTTON8)
		{
			button.second->execute((state & (1 << (button.first-1))) ? 1 : 0, time);
		}
		else if(button.first == RELX)
		{
			button.second->execute(float(-x * 10) / m_width, time);
		}
		else if(button.first == RELY)
		{
			button.second->execute(float(y * 10) / m_height, time);
		}
	}
}
