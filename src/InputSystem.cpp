#include <SDL.h>
#include <vector>

#include "InputSystem.h"
#include "GameApplication.h"
#include "MessageException.h"

#include <boost/foreach.hpp>

InputSystem::InputSystem(GameApplication& ga) :
	GameSystem(ga)
{
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	SDL_JoystickEventState(SDL_ENABLE);
	SDL_ShowCursor(false);

	int width = 640;
	int height = 480;
	IConfiguration& config = ga.getConfig();
	config.getInteger("width", width);
	config.getInteger("height", height);

	m_mouse.reset(new SDLMouse(width, height));
	m_keyboard.reset(new SDLKeyboard());
}

InputSystem::~InputSystem()
{
}

void InputSystem::bind(IConfiguration& config, std::vector<boost::shared_ptr<IInputAction> >& actions)
{
	std::vector<std::string> devices;
	std::vector<std::pair<std::string, std::string> > bindings;

	InputDevice* dev;

	config.getIndexList("input", devices);

	BOOST_FOREACH(std::string& device, devices)
	{
		if(device == "keyboard")
			dev = m_keyboard.get();
		else if(device == "mouse")
			dev = m_mouse.get();
		else
		{
			int id = SDLJoystick::nameToID(device, "joystick");
			if(id >= 0)
			{
				try
				{
					std::map<int, boost::shared_ptr<SDLJoystick> >::iterator it = m_joysticks.find(id);
					if(it == m_joysticks.end())
					{
						m_joysticks[id] = boost::shared_ptr<SDLJoystick>(new SDLJoystick(id));
						it = m_joysticks.find(id);
					}
					dev = it->second.get();
				}
				catch(MessageException&)
				{
					continue;
				}
			}
			else
				continue;
		}

		bindings.clear();

		config.getIndexStringList("input." + device, bindings);

		typedef std::pair<std::string,std::string> temp;
		BOOST_FOREACH(temp& binding, bindings)
		{
			BOOST_FOREACH(boost::shared_ptr<IInputAction>& action, actions)
			{
				if(action->getName() == binding.second)
				{
					dev->addBinding(binding.first, action);
					break;
				}
			}
		}
	}
}

void InputSystem::unBindAll()
{
}

void InputSystem::update(float time)
{
	m_mouse->process(time);
	m_keyboard->process(time);

	typedef std::pair<const int, boost::shared_ptr<SDLJoystick> > temp;
	BOOST_FOREACH(temp& joystick, m_joysticks)
	{
		joystick.second->process(time);
	}
}

void InputSystem::process(SDL_Event& event, float time)
{
	switch(event.type)
	{
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		m_keyboard->process(event, time);
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		m_mouse->process(event, time);
		break;
	case SDL_JOYAXISMOTION:
	case SDL_JOYBALLMOTION:
	case SDL_JOYHATMOTION:
	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
		{
			std::map<int, boost::shared_ptr<SDLJoystick> >::iterator it = m_joysticks.find(event.jaxis.which);
			if(it != m_joysticks.end())
			{
				it->second->process(event, time);
			}
		}
		break;
	}
}
