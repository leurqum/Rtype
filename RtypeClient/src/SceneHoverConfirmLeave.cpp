#include "SceneHoverConfirmLeave.h"

SceneHoverConfirmLeave::SceneHoverConfirmLeave(IScene& decoratedScene, bool homeLink) :
  ASceneHover(decoratedScene), menu("Back")
{
  menu.addButton("Exit !!"); // then exit totally
  // NOTE: I am aware that the user design is not perfect here, because these two opposite buttons shouldn't be next to one another, but it's pretty convenient to code, so f*ck you.

  if (homeLink)
    menu.addButton("Home"); // then Home
  menu.setInitialValue(ValueDrawer(200, 160,0, 0, 0));
}

SceneHoverConfirmLeave::~SceneHoverConfirmLeave(void)
{
}

IScene* SceneHoverConfirmLeave::update(float elapsedTime)
{
  ASceneHover::update(elapsedTime);

  menu.checkInput(SceneManager::getInstance()->getInputManager());
  if (menu.getSelectedId() == 0 && menu.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
    {
      decoratedScene.setToForeground();
      return &this->decoratedScene;
    }
  if (menu.getSelectedId() == 1 && menu.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
    {
      exit(0); // FIXME: well... that's a bit rough.
    }
  if (menu.getSelectedId() == 2 && menu.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
    {
      // NOTE: this is leaked, delete this ?
      return new SceneHoverMenu(*(new SceneBackground()));
    }

  menu.update(elapsedTime);
  return this;
}

void SceneHoverConfirmLeave::draw()
{
  ASceneHover::draw();
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  menu.drawTo(gm);
}

void SceneHoverConfirmLeave::load()
{

}

void SceneHoverConfirmLeave::unload()
{

}

void SceneHoverConfirmLeave::setToBackground()
{
}

void SceneHoverConfirmLeave::setToForeground()
{
  
}
