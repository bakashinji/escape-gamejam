#include <Ogre.h>
#include <OgreFontManager.h>

#include "Escape.h"
#include "LuaConfiguration.h"
#include "MessageException.h"
#include "MainState.h"

Escape::Escape()
{
}

RenderSystem & Escape::getRenderSystem()
{
	return *m_renderer.get();
}

InputSystem & Escape::getInputSystem()
{
	return *m_input.get();
}

void Escape::init()
{
	m_logger.createLog("default.log", true, false, true);

	try
	{
		m_config.reset(new LuaConfiguration("config.lua"));
	}
	catch(MessageException& e)
	{
		Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, e.getMessage());
	}

	if(SDL_Init(SDL_INIT_NOPARACHUTE))
		Ogre::LogManager::getSingleton().logMessage(Ogre::LML_CRITICAL, "Error initializing SDL: " + std::string(SDL_GetError()));

	m_renderer.reset(new RenderSystem(*this));
	SDL_WM_SetCaption("Wings of Concept", NULL);

	/* ResourceGroupManager */
	Ogre::ResourceGroupManager &resGroupMgr = Ogre::ResourceGroupManager::getSingleton();
	resGroupMgr.addResourceLocation("../graphix", "FileSystem");
#ifdef WIN32
#else
	resGroupMgr.addResourceLocation("/usr/share/fonts/TTF", "FileSystem");
#endif
	resGroupMgr.initialiseAllResourceGroups();
	Ogre::FontManager &fontMgr = Ogre::FontManager::getSingleton();
	Ogre::MaterialManager& material_mgr = Ogre::MaterialManager::getSingleton();
	Ogre::ResourcePtr font = fontMgr.create("FreeSans","General");
	font->setParameter("type","truetype");
	font->setParameter("source","DejaVuSans.ttf");
	font->setParameter("size","16");
	font->setParameter("resolution","96");
	font->load();


	m_input.reset(new InputSystem(*this));

	m_game_states["main"] = new MainState(*this);
	pushGameState("main");
}

void Escape::exit()
{
	m_renderer.reset();
	m_input.reset();
	SDL_Quit();
}

void Escape::update(float time)
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			popGameState();
			break;
		default:
			m_input->process(event, time);
			break;
		}
	}

	m_renderer->update(time);
	m_input->update(time);

	SDL_Delay(50);
}
