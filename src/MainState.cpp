#include <Ogre.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>

#include "MainState.h"
#include "QuitAction.h"
#include "MoveActions.h"

MainState::MainState(Escape& woc) :
	GameState(woc),
	m_renderer(woc.getRenderSystem()),
	m_input(woc.getInputSystem())
{
}

MainState::~MainState()
{
}

Ogre::SceneManager * MainState::getSceneManager()
{
	return m_sceneManager;
}

void MainState::load()
{
	/* SceneManager */
	m_sceneManager = m_renderer.getRoot()->createSceneManager(Ogre::ST_EXTERIOR_CLOSE, "sceneManager");
	m_sceneManager->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	m_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	m_sceneManager->setShadowTextureCount(3);
	m_sceneManager->setShadowUseInfiniteFarPlane(false);

	/* Camera */
	m_cam = m_sceneManager->createCamera("cam");
	m_cam->setPosition(Ogre::Vector3(0.0f, 4.0f, -15.0f));
	m_cam->lookAt(Ogre::Vector3(0.0f, 0.0f, 0.0f));
	m_cam->setNearClipDistance(5.0f);
	//	cam->setFarClipDistance(5000.0f);

	/* Viewport */
	Ogre::Viewport* view = m_renderer.getRenderWindow()->addViewport(m_cam);
	view->setBackgroundColour(Ogre::ColourValue(0.2f, 0.2f, 1.0f));
	m_cam->setAspectRatio(Ogre::Real(view->getActualWidth()) / Ogre::Real(view->getActualHeight()));

	/* Plane */
	/*Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
												  1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* planeentity = m_sceneManager->createEntity("GroundEntity", "ground");
	m_sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(planeentity);*/
	/*planeentity->setMaterialName("Examples/Rockwall");
	planeentity->setCastShadows(false);*/

#if 0

	/* Terrain */
	Ogre::Entity* terrain = m_sceneManager->createEntity("Terrain", "Grid.mesh");
	Ogre::SceneNode* node = m_sceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(terrain);
	node->scale(400, 400, 400);

	m_player.reset(new Fighter(*this));

	node = m_player->getNode();
	node->attachObject(m_cam);

	/* Lights */
	/*Ogre::Light* pointlight = m_sceneManager->createLight("PointLight");
	pointlight->setType(Ogre::Light::LT_POINT);
	pointlight->setPosition(Ogre::Vector3(0, 150, 250));
	/*pointlight->setDiffuseColour(1, 0, 0);
	pointlight->setSpecularColour(1, 0, 0);*/

	Ogre::Light* directionallight = m_sceneManager->createLight("DirectionalLight");
	directionallight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionallight->setDirection(Ogre::Vector3(0, -1, 1));
	/*directionallight->setDiffuseColour(.25, .25, 0);
	directionallight->setSpecularColour(.25, .25, 0);*/

	directionallight = m_sceneManager->createLight("DirectionalLight2");
	directionallight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionallight->setDirection(Ogre::Vector3(0, -1, -1));

	/*Ogre::Light* spotlight = sceneManager->createLight("SpotLight");
	spotlight->setType(Ogre::Light::LT_SPOTLIGHT);
	spotlight->setPosition(Ogre::Vector3(300, 300, 0));
	spotlight->setDirection(Ogre::Vector3(-1, -1, 0));
	spotlight->setDiffuseColour(0, 0, 1);
	spotlight->setSpecularColour(0, 0, 1);
	spotlight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));*/


	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", "mainPanel"));
	panel->setDimensions(1, 1);
	panel->setPosition(0, 0);

	m_speed = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", "speed"));
	m_speed->setPosition(0.05, 0.93);
	m_speed->setDimensions(0.1, 0.1);
	m_speed->setCaption("Speed: ");
	m_speed->setCharHeight(0.03);
	m_speed->setFontName("FreeSans");
	m_speed->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
	m_speed->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));

	m_fuell = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", "fuell"));
	m_fuell->setPosition(0.05, 0.90);
	m_fuell->setDimensions(0.1, 0.1);
	m_fuell->setCaption("Fuell: ");
	m_fuell->setCharHeight(0.03);
	m_fuell->setFontName("FreeSans");
	m_fuell->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
	m_fuell->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));

	Ogre::Overlay* overlay = overlayManager.create("mainOverlay");
	overlay->add2D(panel);

	panel->addChild(m_speed);
	panel->addChild(m_fuell);

	overlay->show();

#endif

	std::vector<std::shared_ptr<IInputAction>> actions;
	actions.push_back(std::shared_ptr<IInputAction>(new QuitAction(m_ga)));
	/*actions.push_back(std::shared_ptr<IInputAction>(new AccelerateAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new DragAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new RollLeftAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new RollRightAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new BoostAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new RiseAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new FallAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new LeftAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new RightAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new SteerAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new ClimbAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new RollAction(*m_player.get())));
	actions.push_back(std::shared_ptr<IInputAction>(new ThrustAction(*m_player.get())));*/

	m_input.bind(m_ga.getConfig(), actions);
}

void MainState::update(float time)
{
#if 0
	m_player->update(time);

	std::stringstream sstr;

	sstr << "Speed: " << m_player->getSpeed();
	m_speed->setCaption(sstr.str());

	sstr.str("");
	sstr << "Boost: " << int(m_player->getFuell() / Fighter::MAX_FUELL * 100) << " %";
	m_fuell->setCaption(sstr.str());
#endif
}

void MainState::stop()
{
}

void MainState::start()
{
}

void MainState::unload()
{
}

