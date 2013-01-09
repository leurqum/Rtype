#include "SceneHoverMenu.h"

SceneHoverMenu::SceneHoverMenu(IScene& decoratedScene) :
  ASceneHover(decoratedScene),
  playButton(*SpriteSheetFactory::getInstance()->getSpriteSheet(3)),
  exitButton(*SpriteSheetFactory::getInstance()->getSpriteSheet(3)),
  selectionArrow(*SpriteSheetFactory::getInstance()->getSpriteSheet(4))
{
  playButton.setPosition(Vector2<float>(330, 160));

  exitButton.setPosition(Vector2<float>(330, 200));

  selectionArrow.setPosition(Vector2<float>(310, 160));


  allButtons.addDrawable(&playButton);
  allButtons.addDrawable(&exitButton);

  firstSelection = Vector2<float>(310, 160);
  gapButtons = Vector2<float>(0, 40);
  selectionPosition = 0;
  nbButtons = 2;
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
    {
      ++selectionPosition;
      if (selectionPosition >= nbButtons)
	selectionPosition = 0;
      selectionArrow.
	setPosition(
		    Vector2<float>(firstSelection.x + selectionPosition * gapButtons.x,
				   firstSelection.y + selectionPosition * gapButtons.y));
    }
  const Vector2<bool>& returnKey(sm->getInputManager()->getKeyStatus(sf::Keyboard::Return));
  if (!returnKey.x && returnKey.y)
    {
      // TODO: make this more dynamic (an idea would be to create a LayoutDrawerMenu, with the arrow and stuff).
      if (selectionPosition == 0)
	playButton.animate(1);
      else
	exitButton.animate(1);
    }
  else if (returnKey.x && !returnKey.y)
    // INFO: Validation of current selected button
    return new SceneGame(this->decoratedScene);


  allButtons.update(elapsedTime);
  selectionArrow.update(elapsedTime);

  return this;
}

void SceneHoverMenu::draw()
{
  ASceneHover::draw();
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  allButtons.drawTo(gm);
  selectionArrow.drawTo(gm);
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
