#include "QuitAction.h"

#include "GameApplication.h"

QuitAction::QuitAction(GameApplication &ga) :
	m_ga(ga)
{
}

QuitAction::~QuitAction()
{
}

void QuitAction::execute(float value, float time)
{
	m_ga.popGameState();
}

bool QuitAction::isContinuous()
{
	return false;
}

std::string QuitAction::getName() const
{
	return "quit";
}

