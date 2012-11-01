#include "GameState.h"

GameState::GameState(GameApplication& ga) :
	m_ga(ga), m_count(0)
{
}

GameState::~GameState()
{
}

void GameState::push()
{
	if(!m_count)
	{
		load();
	}

	m_count++;
}

void GameState::pop()
{
	m_count--;

	if(!m_count)
	{
		unload();
	}
}
