#ifndef MOVEACTIONS_H
#define MOVEACTIONS_H

#include "IInputAction.h"
#include "Fighter.h"

class AccelerateAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	AccelerateAction(Fighter& fighter);
	virtual ~AccelerateAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class DragAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	DragAction(Fighter& fighter);
	virtual ~DragAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class RollLeftAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	RollLeftAction(Fighter& fighter);
	virtual ~RollLeftAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class RollRightAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	RollRightAction(Fighter& fighter);
	virtual ~RollRightAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class BoostAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	BoostAction(Fighter& fighter);
	virtual ~BoostAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class RiseAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	RiseAction(Fighter& fighter);
	virtual ~RiseAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class FallAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	FallAction(Fighter& fighter);
	virtual ~FallAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class LeftAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	LeftAction(Fighter& fighter);
	virtual ~LeftAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class RightAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	RightAction(Fighter& fighter);
	virtual ~RightAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class SteerAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	SteerAction(Fighter& fighter);
	virtual ~SteerAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class ClimbAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	ClimbAction(Fighter& fighter);
	virtual ~ClimbAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class RollAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	RollAction(Fighter& fighter);
	virtual ~RollAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

class ThrustAction : public IInputAction
{
private:
	Fighter& m_fighter;
public:
	ThrustAction(Fighter& fighter);
	virtual ~ThrustAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

#endif // MOVEACTIONS_H
