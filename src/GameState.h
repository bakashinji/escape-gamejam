#ifndef GAMESTATE_INCLUDED
#define GAMESTATE_INCLUDED

#include "GameApplication.h"

class GameState
{
	protected:
		GameApplication& m_ga;
		int m_count;

	public:
		GameState(GameApplication& ga);
		virtual ~GameState();

		void push();
		void pop();

		virtual void load()=0;
		virtual void unload()=0;
		virtual void start()=0;
		virtual void stop()=0;
		virtual void update(float time)=0;
};

#endif
