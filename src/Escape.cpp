#include <Ogre.h>
#include <OgreFontManager.h>

#include "Escape.h"
#include "LuaConfiguration.h"
#include "MessageException.h"
#include "MainState.h"

Escape::Escape() :
	m_input(NULL),
	m_renderer(NULL)
{
}

Escape::~Escape()
{
	delete m_renderer;
	delete m_input;
}

RenderSystem & Escape::getRenderSystem()
{
	return *m_renderer;
}

InputSystem & Escape::getInputSystem()
{
	return *m_input;
}

void Escape::init()
{
	m_logger.createLog("default.log", true, false, true);

	try
	{
		delete m_config;
		m_config = new LuaConfiguration("config.lua");
	}
	catch(MessageException& e)
	{
		Ogre::LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, e.getMessage());
	}

	if(SDL_Init(SDL_INIT_NOPARACHUTE))
		Ogre::LogManager::getSingleton().logMessage(Ogre::LML_CRITICAL, "Error initializing SDL: " + std::string(SDL_GetError()));


	delete m_renderer;
	m_renderer = new RenderSystem(*this);
  SDL_WM_SetCaption("Escape", NULL);

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


	delete m_input;
	m_input = new InputSystem(*this);

	m_game_states["main"] = new MainState(*this);
	pushGameState("main");
}

void Escape::exit()
{
	delete m_renderer;
	delete m_input;

	m_renderer = NULL;
	m_input = NULL;

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
