#ifndef QUITACTION_H
#define QUITACTION_H

#include "IInputAction.h"

class GameApplication;

class QuitAction : public IInputAction
{
private:
	GameApplication& m_ga;
public:
	QuitAction(GameApplication& ga);
	virtual ~QuitAction();

	virtual void execute(float value, float time);
	virtual bool isContinuous();
	virtual std::string getName() const;
};

#endif // QUITACTION_H
