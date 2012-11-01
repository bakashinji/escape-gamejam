#ifndef COMBATACTIONS_H
#define COMBATACTIONS_H

#include "IInputAction.h"

class FireAction : public IInputAction
{
public:
	FireAction();
	virtual ~FireAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class SecondaryAction : public IInputAction
{
public:
	SecondaryAction();
	virtual ~SecondaryAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class FlareAction : public IInputAction
{
public:
	FlareAction();
	virtual ~FlareAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class NextTargetAction : public IInputAction
{
public:
	NextTargetAction();
	virtual ~NextTargetAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

#endif // COMBATACTIONS_H
