#include <sstream>

#include "InputDevice.h"

int InputDevice::nameToID(const std::string &text, const std::string &start)
{
	int id = -1;

	if(!startsWith(text, start))
		return id;

	std::stringstream ss(text.substr(start.length()));

	ss >> id;

	return id;
}

bool InputDevice::startsWith(const std::string &text, const std::string &start)
{
	return !text.compare(0, start.length(), start);
}

InputDevice::InputDevice()
{
}

InputDevice::~InputDevice()
{
}

bool InputDevice::addBinding(std::string name, std::shared_ptr<IInputAction> action)
{
	int id = translate(name);
	if(id == NOT_FOUND)
		return false;

	if(action->isContinuous())
		m_continuous[id] = action;
	else
		m_bindings[id] = action;

	return true;
}

bool InputDevice::removeBinding(std::string name, std::shared_ptr<IInputAction> action)
{
	int id = translate(name);
	if(id == NOT_FOUND)
		return false;

	auto it = m_bindings.find(id);
	if(it != m_bindings.end())
	{
		m_bindings.erase(it);
		return true;
	}

	auto it2 = m_continuous.find(id);
	if(it2 != m_continuous.end())
	{
		m_continuous.erase(it2);
		return true;
	}

	return false;
}

void InputDevice::fire(int id, float value, float time)
{
	auto res = m_bindings.find(id);

	if(res != m_bindings.end())
	{
		(*res).second->execute(value, time);
	}
}
