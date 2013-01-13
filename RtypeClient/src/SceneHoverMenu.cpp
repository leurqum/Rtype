#include "SceneHoverMenu.h"

SceneHoverMenu::SceneHoverMenu(IScene& decoratedScene) :
  ASceneHover(decoratedScene)
{
  menu.addButton();
  menu.setInitialValue({{200, 160},{0, 0}, 0});
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

  menu.setInitialValue({d.position - 50, d.scale, d.rotation});
  std::list<ValueDrawer > toBgAnimation;
  toBgAnimation.push_back({{0,0},{0,0}, 0});
  toBgAnimation.push_back({{-100, -50},{-0.2,-0.2},0}); // TODO: scaling :D

  menu.setAnimation((new Animation<ValueDrawer>(toBgAnimation, 500, true)), 490);

}

void SceneHoverMenu::setToForeground()
{

}
