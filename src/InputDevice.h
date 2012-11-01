#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <unordered_map>
#include <string>
#include <memory>

#include "IInputAction.h"

class InputDevice
{
protected:
	std::unordered_map<int, std::shared_ptr<IInputAction>> m_bindings;
	std::unordered_map<int, std::shared_ptr<IInputAction>> m_continuous;

	static const int NOT_FOUND = 0x80000000;

public:
	static int nameToID(const std::string& text, const std::string& start);
	static bool startsWith(const std::string& text, const std::string& start);

	InputDevice();
	virtual ~InputDevice();

	bool addBinding(std::string name, std::shared_ptr<IInputAction> action);
	bool removeBinding(std::string name, std::shared_ptr<IInputAction> action);
	void fire(int id, float value, float time);

	virtual int translate(std::string name)=0;
	virtual void process(float time)=0;
};

#endif // INPUTDEVICE_H
