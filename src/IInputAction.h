#ifndef IINPUTACTION_H
#define IINPUTACTION_H

#include <string>

class IInputAction
{
public:
	virtual void execute(float value, float time)=0;
	virtual bool isContinuous()=0;
	virtual std::string getName() const=0;
};

#endif // IINPUTACTION_H
