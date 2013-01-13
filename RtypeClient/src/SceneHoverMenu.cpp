#include "SceneHoverMenu.h"

SceneHoverMenu::SceneHoverMenu(IScene& decoratedScene) :
  ASceneHover(decoratedScene)
{
  menu.addButton();
  menu.setInitialValue({{200, 160},{1, 1}, 0});
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

  menu.setInitialValue({d.position - 50, d.scale - 0.2, d.rotation});
}

void SceneHoverMenu::setToForeground()
{

}
