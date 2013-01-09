#include "SceneGame.h"

SceneGame::SceneGame(IScene& decoratedScene) : ASceneHover(decoratedScene)
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
  IScene* ret = ASceneHover::update(elapsedTime);
  if (ret != getParentScene())
	  // FIXME: I don't know if the following scenario would be safe...
    return ret; // some decorated scene have changed the scene :(

  //std::cout << "scenegame update" << std::endl;
  // TODO: (not here but in SceneHoverWhatever) update background scenes ?
  // TODO: update the scene depending on network data received.
  Protocol::drawable d;
  d.id = 0;
  d.type = Protocol::SHIP;
  static int x = 490;
  static int incr = 5;

  d.xPosition = x;
   // x += incr;
   // if (x > 500)
   //   incr = -5;
   // if (x <= 400)
   //   incr = 5;
  d.yPosition = 123;


  if (ship[0] != nullptr)
    {
      // NOTE: we assume d.type is the right type for old, if it's a wrong type, then it's messed up earlier. (but this class doesn't care, it's Drawable who will handle (or not) the matter.)
      ship[0]->setUpdate(d);
    }
  else
    {

      DrawableRemote* ret = new DrawableRemote();
      ret->setUpdate(d);

      ship[0] = ret;
    }

  // TODO: insert input managing code here.

  ship[0]->update(elapsedTime);
 //fixedBackground.update(elapsedTime);
 //scrollingBackground.update(elapsedTime);
 //scrollingBackground2.update(elapsedTime);
  std::cout << "scenegame END update" << std::endl;
  return this;
}

void SceneGame::draw()
{
  ASceneHover::draw();

  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  //gm->draw(&fixedBackground);
  //std::cout << "drawing" << std::endl;
  //gm->draw(&scrollingBackground);
  //gm->draw(&scrollingBackground2);
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
