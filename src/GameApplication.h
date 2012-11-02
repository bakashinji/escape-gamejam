#ifndef GAMEAPPLICATION_INCLUDED
#define GAMEAPPLICATION_INCLUDED

#include <memory>
#include <map>
#include <stack>
#include <string>
#include "unique_ptr.h"

#include "IConfiguration.h"

class GameState;

class GameApplication
{
	protected:
		std::map<std::string, GameState*> m_game_states;
		std::stack<GameState*> m_states_stack;
		unique_ptr(IConfiguration) m_config;

	public:
		virtual ~GameApplication();

		IConfiguration& getConfig();

		void run();
		void play();
		void switchGameState(std::string name);
		void pushGameState(std::string name);
		void popGameState();

		virtual void init()=0;
		virtual void exit()=0;
		virtual void update(float time)=0;
};

#endif
