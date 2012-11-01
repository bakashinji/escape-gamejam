#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

class GameApplication;

class GameSystem
{
protected:
	GameApplication& m_ga;
public:
	GameSystem(GameApplication& ga);
	virtual ~GameSystem();

	virtual void update(float time)=0;
};

#endif // GAMESYSTEM_H
