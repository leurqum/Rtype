#include "SceneHoverMenu.h"

SceneHoverMenu::SceneHoverMenu(IScene& decoratedScene) : ASceneHover(decoratedScene)
{
  playButton.setSpriteSheet(SpriteSheetFactory::getInstance()->getSpriteSheet(3));
  playButton.setPosition(330, 160);
  playButton.animate(0);

  searchGameButton.setSpriteSheet(SpriteSheetFactory::getInstance()->getSpriteSheet(3));
  searchGameButton.setPosition(330, 200);
  searchGameButton.animate(0);

  selectionArrow.setSpriteSheet(SpriteSheetFactory::getInstance()->getSpriteSheet(4));
  selectionArrow.setPosition(310, 160);
  selectionArrow.animate(0);


}


SceneHoverMenu::~SceneHoverMenu(void)
{
}

IScene* SceneHoverMenu::update(float elapsedTime)
{
  ASceneHover::update(elapsedTime);

  SceneManager* sm = SceneManager::getInstance();

  const Vector2<bool>& downKey(sm->getInputManager()->getKeyStatus(sf::Keyboard::Down));
  if (downKey.x && !downKey.y)
    selectionArrow.setPosition(selectionArrow.getPosition().x, selectionArrow.getPosition().y + 40);

  const Vector2<bool>& returnKey(sm->getInputManager()->getKeyStatus(sf::Keyboard::Return));
  if (!returnKey.x && returnKey.y)
	  playButton.animate(1);
  else if (returnKey.x && !returnKey.y)
	// INFO: Validation of current selected button
	return new SceneGame(this->decoratedScene);


  playButton.update(elapsedTime);
  searchGameButton.update(elapsedTime);
  selectionArrow.update(elapsedTime);

  return this;
}

void SceneHoverMenu::draw()
{
	ASceneHover::draw();
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  gm->draw(&playButton);
  gm->draw(&searchGameButton);
  gm->draw(&selectionArrow);
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
