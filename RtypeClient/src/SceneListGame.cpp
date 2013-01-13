#include "SceneListGame.h"

SceneListGame::SceneListGame(IScene& decoratedScene) :
  ASceneHover(decoratedScene)
{
  menuGames.addButton();
  menuGames.setInitialValue({{400, 160},{1, 1}, 0});
}


SceneListGame::~SceneListGame(void)
{
}

IScene* SceneListGame::update(float elapsedTime)
{
  ASceneHover::update(elapsedTime);
  menuGames.checkInput(SceneManager::getInstance()->getInputManager());
  menuGames.update(elapsedTime);
  if (menuGames.getSelectedId() == 1 && menuGames.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
    {
      return SceneManager::getInstance()->changeScene(new SceneGame(* (new SceneBackground())));
      // return new SceneGame(this->decoratedScene);
    }
// if (menuGames.getSelectedId() == 1 && menuGames.getSelectionType() == DrawerMenu::selectionType::VALIDATED)
//     return new SceneGame(this->decoratedScene);

  return this;
}

void SceneListGame::draw()
{
  ASceneHover::draw();
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  menuGames.drawTo(gm);
}

void SceneListGame::load()
{

}

void SceneListGame::unload()
{

}

void SceneListGame::setToBackground()
{

}

void SceneListGame::setToForeground()
{

}
