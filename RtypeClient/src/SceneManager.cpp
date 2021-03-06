#include "SceneManager.h"

SceneManager::SceneManager() : current(nullptr), graphicManager(new GraphicsManagerSFML()) // FIXME: ugly hard coded ref to SFML
{
	inputManager = new InputManagerSFML();
}


SceneManager::~SceneManager(void)
{
}

SceneManager* SceneManager::instance = nullptr;

SceneManager* SceneManager::getInstance()
{
  if (instance == nullptr)
    instance = new SceneManager();
  return instance;
}

void SceneManager::update(float milliseconds)
{
  inputManager->update();
  // NOTE: this assignation allows the scene to manage its own decorators.
  current = current->update(milliseconds);
}

void SceneManager::draw()
{
  current->draw();
}

IScene* SceneManager::changeScene(IScene* newScene)
{
  // NOTE: current implementation is a blocking process, think about threading or implementing callbacks.
  if (current)
    current->unload();
  // delete current;
  current = newScene;
  //   NOTE: although unload is blocking, load() might not be : we will then call upgrade upon the current scene.
  //   NOTE: because unload is blocking, if unload display a long animation, next milliseconds for the upgrade function will be awfully long.
  current->load();
  return current;
}

IScene* SceneManager::getCurrentScene()
{
  return current;
}

IGraphicsManager* SceneManager::getGraphicsManager()
{
  return graphicManager;
}

IInputManagerSFML* SceneManager::getInputManager()
{
	return inputManager;
}
