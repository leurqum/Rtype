#include "SceneGame.h"

SceneGame::SceneGame(void)
{
  ship[0] = nullptr;
  ship[1] = nullptr;
  ship[2] = nullptr;
  ship[3] = nullptr;
}

SceneGame::~SceneGame(void)
{
}

IScene* SceneGame::update(float elapsedTime)
{
  // TODO: update background scenes ?
	
  // TODO: update the scene depending on network data received.
  Protocol::drawable d;
  d.id = 0;
  d.type = Protocol::SHIP;
  static int x = 0;
  static int incr = 1;

  d.xPosition = x;
  x += incr;
  if (x > 10)
    incr = -1;
  if (x <= 0)
    incr = 1;
  d.yPosition = 123;

  ship[0] = SceneManager::getInstance()->getGraphicsManager()->updateDrawableFrom(d);

  // TODO: insert input managing code here.

  ship[0]->update(elapsedTime);
  return this;
}

void SceneGame::draw()
{
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();

  // FIXME: use a list ?
  if (ship[0] != nullptr)
    gm->draw(ship[0]);
  if (ship[1] != nullptr)
    gm->draw(ship[1]);
  if (ship[2] != nullptr)
    gm->draw(ship[2]);
  if (ship[3] != nullptr)
    gm->draw(ship[3]);
}

void SceneGame::load()
{

}

void SceneGame::unload()
{

}

void SceneGame::setToBackground()
{

}

void SceneGame::setToForeground()
{

}
