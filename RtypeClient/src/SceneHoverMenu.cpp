#include "SceneHoverMenu.h"

SceneHoverMenu::SceneHoverMenu(IScene& decoratedScene) : ASceneHover(decoratedScene)
{
  std::cout << "scenegame construct" << std::endl;
  playButton.setSpriteSheet(SpriteSheetFactory::getInstance()->getSpriteSheet(3));
  std::cout << "scenegame multiple construct" << std::endl;
  playButton.setPosition(330, 160);
  std::cout << "scenegame after setposition" << std::endl;
  playButton.animate(0);
  std::cout << "scenegame END construct" << std::endl;
}


SceneHoverMenu::~SceneHoverMenu(void)
{
}

IScene* SceneHoverMenu::update(float elapsedTime)
{
  ASceneHover::update(elapsedTime);
  playButton.update(elapsedTime);
  return this;
}

void SceneHoverMenu::draw()
{
	ASceneHover::draw();
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  gm->draw(&playButton);
}

void SceneHoverMenu::load()
{

}

void SceneHoverMenu::unload()
{

}

void SceneHoverMenu::setToBackground()
{

}

void SceneHoverMenu::setToForeground()
{

}
