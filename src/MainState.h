#ifndef MAINSTATE_H
#define MAINSTATE_H

#include "GameState.h"
#include "Escape.h"

class RenderSystem;
class InputSystem;
//class Fighter;

namespace Ogre
{
	class TextAreaOverlayElement;
}

class MainState : public GameState
{
private:
	RenderSystem& m_renderer;
	InputSystem& m_input;

	Ogre::SceneManager* m_sceneManager;
	Ogre::Camera* m_cam;
	Ogre::TextAreaOverlayElement* m_speed;
	Ogre::TextAreaOverlayElement* m_fuell;

	//std::unique_ptr<Fighter> m_player;

public:
	MainState(Escape& woc);
	virtual ~MainState();

	Ogre::SceneManager* getSceneManager();

	virtual void load();
	virtual void unload();
	virtual void start();
	virtual void stop();
	virtual void update(float time);
};

#endif // MAINSTATE_H
