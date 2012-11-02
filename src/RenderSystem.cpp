#include <Ogre.h>

#include "RenderSystem.h"
#include "GameApplication.h"
#include "MessageException.h"

#include <boost/foreach.hpp>

RenderSystem::RenderSystem(GameApplication &ga) :
	GameSystem(ga)
{
	int width = 640;
	int height = 480;
	bool windowed = true;
	int bbp = 32;

	std::string plugindir;
	std::vector<std::string> plugins;

	IConfiguration& config = ga.getConfig();

	config.getInteger("width", width);
	config.getInteger("height", height);
	config.getBoolean("windowed", windowed);
	config.getInteger("bbp", bbp);
	config.getString("plugindir", plugindir);
	config.getStringList("plugins", plugins);

	// SDL Setup

	if(SDL_InitSubSystem(SDL_INIT_VIDEO))
		throw MessageException("Error initializing SDL: " + std::string(SDL_GetError()), MET_ERROR);

	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	if(!(m_screen = SDL_SetVideoMode(width, height, bbp, SDL_OPENGL | SDL_DOUBLEBUF | (windowed ? 0 : SDL_FULLSCREEN))))
	{
		SDL_Quit();
		throw MessageException("Error setting videomode: " + std::string(SDL_GetError()), MET_ERROR);
	}

	// OGRE Setup

	m_root = new Ogre::Root("", "", "");

	BOOST_FOREACH(std::string& plugin, plugins)
		m_root->loadPlugin(plugindir + "/" + plugin);

	m_root->setRenderSystem(m_root->getAvailableRenderers().front());

	m_root->initialise(false);

	// SDL + OGRE Setup

	Ogre::NameValuePairList misc;

#ifdef WINDOWS
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWMInfo(&wmInfo);

	size_t winHandle = reinterpret_cast<size_t>(wmInfo.window);
	size_t winGlContext = reinterpret_cast<size_t>(wmInfo.hglrc);

	misc["externalWindowHandle"] = Ogre::StringConverter::toString(winHandle);
	misc["externalGLContext"] = Ogre::StringConverter::toString(winGlContext);
#else
	misc["currentGLContext"] = Ogre::String("True");
#endif
	m_renderWindow = m_root->createRenderWindow("MainRenderWindow", width, height, !windowed, &misc);
	m_renderWindow->setVisible(true);
}

RenderSystem::~RenderSystem()
{
	m_renderWindow->destroy();
	delete m_root;
}

Ogre::Root* RenderSystem::getRoot() const
{
	return m_root;
}

Ogre::RenderWindow * RenderSystem::getRenderWindow() const
{
	return m_renderWindow;
}

void RenderSystem::update(float time)
{
	m_root->renderOneFrame();
}
