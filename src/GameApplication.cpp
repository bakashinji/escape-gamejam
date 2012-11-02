#include <SDL.h>

#include "GameApplication.h"
#include "GameState.h"
#include "MessageException.h"

GameApplication::GameApplication() :
	m_config(NULL)
{
}

GameApplication::~ GameApplication()
{
	if(!m_states_stack.empty())
	{
		GameState* gs = m_states_stack.top();
		gs->stop();
		while(!m_states_stack.empty())
		{
			gs = m_states_stack.top();
			gs->pop();
			m_states_stack.pop();
		}
	}

	while(!m_game_states.empty())
	{
		std::map<std::string, GameState*>::iterator begin = m_game_states.begin();
		delete begin->second;
		m_game_states.erase(begin);
	}

	delete m_config;
}

IConfiguration& GameApplication::getConfig()
{
	return *m_config;
}

void GameApplication::run()
{
	float time = 0.0f;

	int starttime = SDL_GetTicks();
	int lasttime = SDL_GetTicks();

	GameState* current;

	while(!m_states_stack.empty())
	{
		current = m_states_stack.top();

		starttime = SDL_GetTicks();

		time = (starttime - lasttime) / 1000.0f;
		lasttime = starttime;

		update(time);
		current->update(time);
	}
}

void GameApplication::play()
{
	init();
	run();
	exit();
}

void GameApplication::switchGameState(std::string name)
{
	popGameState();
	pushGameState(name);
}

void GameApplication::pushGameState(std::string name)
{
	std::map<std::string, GameState*>::iterator newState = m_game_states.find(name);

	if(newState != m_game_states.end())
	{
		GameState* gs = newState->second;

		gs->push();
		gs->start();

		m_states_stack.push(gs);
	}
	else
	{
		throw MessageException("Game state " + name + " not found!", ERROR);
	}
}

void GameApplication::popGameState()
{
	if(!m_states_stack.empty())
	{
		GameState* gs = m_states_stack.top();
		m_states_stack.pop();

		gs->stop();
		gs->pop();
	}
}
