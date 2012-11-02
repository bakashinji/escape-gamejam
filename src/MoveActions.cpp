#include "MoveActions.h"

#if 0
/***************** AccelerateAction ********************/

AccelerateAction::AccelerateAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

AccelerateAction::~AccelerateAction()
{
}

void AccelerateAction::execute(float value, float time)
{
	m_fighter.accelerate(value * time);
}

bool AccelerateAction::isContinuous()
{
	return true;
}

std::string AccelerateAction::getName() const
{
	return "accelerate";
}

/***************** DragAction ********************/

DragAction::DragAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

DragAction::~DragAction()
{
}

void DragAction::execute(float value, float time)
{
	m_fighter.accelerate(-value * time);
}

bool DragAction::isContinuous()
{
	return true;
}

std::string DragAction::getName() const
{
	return "drag";
}

/***************** RollLeftAction ********************/

RollLeftAction::RollLeftAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

RollLeftAction::~RollLeftAction()
{
}

void RollLeftAction::execute(float value, float time)
{
	m_fighter.roll(-value * time);
}

bool RollLeftAction::isContinuous()
{
	return true;
}

std::string RollLeftAction::getName() const
{
	return "roll left";
}

/***************** RollRightAction ********************/

RollRightAction::RollRightAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

RollRightAction::~RollRightAction()
{
}

void RollRightAction::execute(float value, float time)
{
	m_fighter.roll(value * time);
}

bool RollRightAction::isContinuous()
{
	return true;
}

std::string RollRightAction::getName() const
{
	return "roll right";
}

/***************** BoostAction ********************/

BoostAction::BoostAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

BoostAction::~BoostAction()
{
}

void BoostAction::execute(float value, float time)
{
	m_fighter.boost(value);
}

bool BoostAction::isContinuous()
{
	return false;
}

std::string BoostAction::getName() const
{
	return "boost";
}

/***************** RiseAction ********************/

RiseAction::RiseAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

RiseAction::~RiseAction()
{
}

void RiseAction::execute(float value, float time)
{
	m_fighter.climb(value * time);
}

bool RiseAction::isContinuous()
{
	return true;
}

std::string RiseAction::getName() const
{
	return "rise";
}

/***************** FallAction ********************/

FallAction::FallAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

FallAction::~FallAction()
{
}

void FallAction::execute(float value, float time)
{
	m_fighter.climb(-value * time);
}

bool FallAction::isContinuous()
{
	return true;
}

std::string FallAction::getName() const
{
	return "fall";
}

/***************** LeftAction ********************/

LeftAction::LeftAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

LeftAction::~LeftAction()
{
}

void LeftAction::execute(float value, float time)
{
	m_fighter.rotate(value * time);
}

bool LeftAction::isContinuous()
{
	return true;
}

std::string LeftAction::getName() const
{
	return "left";
}

/***************** RightAction ********************/

RightAction::RightAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

RightAction::~RightAction()
{
}

void RightAction::execute(float value, float time)
{
	m_fighter.rotate(-value * time);
}

bool RightAction::isContinuous()
{
	return true;
}

std::string RightAction::getName() const
{
	return "right";
}

/***************** SteerAction ********************/

SteerAction::SteerAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

SteerAction::~SteerAction()
{
}

void SteerAction::execute(float value, float time)
{
	m_fighter.rotate(value * time);
}

bool SteerAction::isContinuous()
{
	return true;
}

std::string SteerAction::getName() const
{
	return "steer";
}

/***************** ClimbAction ********************/

ClimbAction::ClimbAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

ClimbAction::~ClimbAction()
{
}

void ClimbAction::execute(float value, float time)
{
	m_fighter.climb(value * time);
}

bool ClimbAction::isContinuous()
{
	return true;
}

std::string ClimbAction::getName() const
{
	return "climb";
}

/***************** RollAction ********************/

RollAction::RollAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

RollAction::~RollAction()
{
}

void RollAction::execute(float value, float time)
{
	m_fighter.roll(value * time);
}

bool RollAction::isContinuous()
{
	return true;
}

std::string RollAction::getName() const
{
	return "roll";
}

/***************** ThrustAction ********************/

ThrustAction::ThrustAction(Fighter& fighter) :
	m_fighter(fighter)
{
}

ThrustAction::~ThrustAction()
{
}

void ThrustAction::execute(float value, float time)
{
	m_fighter.accelerate(value * time);
}

bool ThrustAction::isContinuous()
{
	return true;
}

std::string ThrustAction::getName() const
{
	return "thrust";
}

#endif
