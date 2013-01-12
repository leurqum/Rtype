#include "SceneHoverMenu.h"

SceneHoverMenu::SceneHoverMenu(IScene& decoratedScene) :
  ASceneHover(decoratedScene) ,
  playButton(*SpriteSheetFactory::getInstance()->getSpriteSheet(3)),
  _playButton(playButton),
  exitButton(*SpriteSheetFactory::getInstance()->getSpriteSheet(3)),
  _exitButton(exitButton),
  selectionArrow(*SpriteSheetFactory::getInstance()->getSpriteSheet(4)),
  _selectionArrow(selectionArrow)
{
  _playButton.setInitialValue({{330, 160}, {1, 1}, 0});

  _exitButton.setInitialValue({{330, 200}, {1, 1}, 0});

  _selectionArrow.setInitialValue({{310, 160}, {1, 1}, 0});

  std::list<ValueDrawer > arrowAnimation;
  arrowAnimation.push_back({{0,0},{1,1}, 0});
  arrowAnimation.push_back({{-10, 0},{1,1},0});
  _selectionArrow.setAnimation((new Animation<ValueDrawer>(arrowAnimation, 500, true, 0, true)));

  // allButtons.addDrawable(&playButton);
  // allButtons.addDrawable(&exitButton);

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
      _selectionArrow.
  	setInitialValue(
			{{firstSelection.x + selectionPosition * gapButtons.x,
			      firstSelection.y + selectionPosition * gapButtons.y},
			    {1, 1}, 0});
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


  // allButtons.update(elapsedTime);
  playButton.update(elapsedTime);
  _playButton.update(elapsedTime);
  exitButton.update(elapsedTime);
  _exitButton.update(elapsedTime);

  selectionArrow.update(elapsedTime);
  _selectionArrow.update(elapsedTime);
  return this;
}

void SceneHoverMenu::draw()
{
  ASceneHover::draw();
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  _playButton.drawTo(gm);
  _exitButton.drawTo(gm);
  // allButtons.drawTo(gm);
  _selectionArrow.drawTo(gm);
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
