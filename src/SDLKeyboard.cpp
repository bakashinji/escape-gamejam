#include <SDL_keyboard.h>

#include <boost/foreach.hpp>

#include "SDLKeyboard.h"

SDLKeyboard::SDLKeyboard()
{
}

SDLKeyboard::~SDLKeyboard()
{
}

void SDLKeyboard::process(SDL_Event &event, float time)
{
	switch(event.type)
	{
	case SDL_KEYDOWN:
		fire(event.key.keysym.sym, 1, time);
		break;
	case SDL_KEYUP:
		fire(event.key.keysym.sym, 0, time);
		break;
	}
}

#include <iostream>

int SDLKeyboard::translate(std::string name)
{
	if(name == "")
		return NOT_FOUND;

	int numkeys;
	Uint8* state = SDL_GetKeyState(&numkeys);

	for(int key = 0; key < numkeys; key++)
	{
		if(name == SDL_GetKeyName(static_cast<SDLKey>(key)))
			return key;
	}

	return NOT_FOUND;
}

void SDLKeyboard::process(float time)
{
	int numkeys;

	Uint8* state = SDL_GetKeyState(&numkeys);

	typedef std::pair<const int, boost::shared_ptr<IInputAction> > temp;
	BOOST_FOREACH(temp& button, m_continuous)
	{
		button.second->execute(state[button.first], time);
	}
}
