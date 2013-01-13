#include "SceneHoverMenu.h"

SceneHoverMenu::SceneHoverMenu(IScene& decoratedScene) :
  ASceneHover(decoratedScene)
{
  menu.addButton();
  menu.setInitialValue(ValueDrawer(200, 160,0, 0, 0));
  isBackground = false;
}


SceneHoverMenu::~SceneHoverMenu(void)
{
}

IScene* SceneHoverMenu::update(float elapsedTime)
{
  ASceneHover::update(elapsedTime);

  if (!isBackground)
    {
      menu.checkInput(SceneManager::getInstance()->getInputManager());
      if (menu.getSelectedId() == 0 && menu.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
	return new SceneGame(this->decoratedScene);
      if (menu.getSelectedId() == 1 && menu.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
	{
	  
	  return new SceneListGame(*this);
	}
    }
  menu.update(elapsedTime);
  return this;
}

void SceneHoverMenu::draw()
{
  ASceneHover::draw();
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  menu.drawTo(gm);
}

void SceneHoverMenu::load()
{

}

void SceneHoverMenu::unload()
{

}

void SceneHoverMenu::setToBackground()
{
  isBackground = true;
  ValueDrawer d = menu.getInitialValue();

  std::list<ValueDrawer > toBgAnimation;
  toBgAnimation.push_back(ValueDrawer());
  toBgAnimation.push_back(ValueDrawer(-200, -50, -0.3, -0.3)); // TODO: scaling :D

  menu.setAnimation((new Animation<ValueDrawer>(toBgAnimation, 500, true)), 490);
}

void SceneHoverMenu::setToForeground()
{

}
