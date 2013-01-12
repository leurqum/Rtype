#include "SceneHoverMenu.h"

SceneHoverMenu::SceneHoverMenu(IScene& decoratedScene) :
  ASceneHover(decoratedScene)
{
  menu.addButton();
  menu.setInitialValue({{200, 160},{1, 1}, 0});
}


SceneHoverMenu::~SceneHoverMenu(void)
{
}

IScene* SceneHoverMenu::update(float elapsedTime)
{
  ASceneHover::update(elapsedTime);

  menu.update(elapsedTime);
  if (menu.getSelectedId() == 0 && menu.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
    return new SceneGame(this->decoratedScene);
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

}

void SceneHoverMenu::setToForeground()
{

}
