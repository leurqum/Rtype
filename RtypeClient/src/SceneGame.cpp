#include "SceneGame.h"

SceneGame::SceneGame(IScene& decoratedScene) :
  ASceneHover(decoratedScene)
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


  if (ship[0] == nullptr)
    {
      ship[0] = new DrawerShip(0);
    }
  // NOTE: we assume d.type is the right type for old, if it's a wrong type, then it's messed up earlier. (but this class doesn't care, it's Drawable who will handle (or not) the matter.)
  ship[0]->setUpdate(d);
  // TODO: insert input managing code here.

  d.id = 0;
  d.type = Protocol::SHIP;
  static int _x = 480;
  static int _y = 223;
  static int _incr = 2;

  d.xPosition = _x;
  // _x += _incr;
  // _y += _incr;
  //  if (_x > 500)
  //    _incr = -5;
  //  if (_x <= 400)
  //    _incr = 5;

  d.yPosition = _y;
  enemy.setUpdate(d);
  enemy.update(elapsedTime);


  ship[0]->update(elapsedTime);
  std::cout << "scenegame END update" << std::endl;
  return this;
}

void SceneGame::draw()
{
  ASceneHover::draw();


  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();

  enemy.drawTo(gm);


  if (ship[0] != nullptr)
    ship[0]->drawTo(gm);
  if (ship[1] != nullptr)
    ship[0]->drawTo(gm);
  if (ship[2] != nullptr)
    ship[0]->drawTo(gm);
  if (ship[3] != nullptr)
    ship[0]->drawTo(gm);
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
