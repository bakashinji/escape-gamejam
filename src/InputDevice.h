#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <memory>

#include "IInputAction.h"

class InputDevice
{
protected:
	boost::unordered_map<int, boost::shared_ptr<IInputAction> > m_bindings;
	boost::unordered_map<int, boost::shared_ptr<IInputAction> > m_continuous;

	static const int NOT_FOUND = 0x80000000;

public:
	static int nameToID(const std::string& text, const std::string& start);
	static bool startsWith(const std::string& text, const std::string& start);

	InputDevice();
	virtual ~InputDevice();

	bool addBinding(std::string name, boost::shared_ptr<IInputAction> action);
	bool removeBinding(std::string name, boost::shared_ptr<IInputAction> action);
	void fire(int id, float value, float time);

	virtual int translate(std::string name)=0;
	virtual void process(float time)=0;
};

#endif // INPUTDEVICE_H
