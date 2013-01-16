#include "SceneGame.h"

SceneGame::SceneGame(IScene& decoratedScene, Network* net) :
	ASceneHover(decoratedScene), network(net)
{
  ship[0] = nullptr;
  ship[1] = nullptr;
  ship[2] = nullptr;
  ship[3] = nullptr;
  drawer_2bars.setBar1(100);
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

  // TODO: update the scene depending on network data received.
  // Protocol::drawable d;
  // d.id = 0;
  // d.type = Protocol::SHIP;
  // static int x = 490;
  // static int incr = 5;

  // d.xPosition = x;
  //  x += incr;
  //  if (x > 500)
  //    incr = -5;
  //  if (x <= 400)
  //    incr = 5;
  // d.yPosition = 123;


  // NOTE: we assume d.type is the right type for old, if it's a wrong type, then it's messed up earlier. (but this class doesn't care, it's Drawable who will handle (or not) the matter.)
  
  bool recved = true;
  while (recved)
    {
      Protocol::drawable d = network->GetPieceWorld(recved);
      // std::cout << "new update !" << std::endl;
      if (recved && d.type == Protocol::type_drawable::SHIP)
	{
	  // std::cout << "i'ts a ship !" << std::endl;
	  // std::cout << d.xPosition << ";" << d.yPosition << std::endl;
	  if (ship[0] == nullptr)
	    {
	      ship[0] = new DrawerShip(0);
	    }
	  ship[0]->setUpdate(d);
	}
    }
// #define pos(x) ((x) > 0 ? (x) : -(x))
//   drawer_2bars.setBar1(pos(x - 500));

//   d.id = 0;
//   d.type = Protocol::SHIP;
//   static int _x = 480;
//   static int _y = 223;
//   static int _incr = 2;

//   drawer_2bars.setBar2(pos(_x - 400));
//   // drawer_2bars.setBar2(100);

//   d.xPosition = _x;
//   _x += _incr;
//   _y += _incr;
//    if (_x > 500)
//      _incr = -3;
//    if (_x <= 400)
//      _incr = 3;

//   d.yPosition = _y;
//   enemy.setUpdate(d);

//   enemy.update(elapsedTime);
  if (ship[0])
    ship[0]->update(elapsedTime);
  drawer_2bars.update(elapsedTime);


  // std::cout << "scenegame END update" << std::endl;
  return manageInput(); // manage input before updates would improve responsiveness if we take it into account for our drawings, but we don't do this for the moment, so it would add unnessecary complexity.
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
  // drawer_2bars.drawTo(gm);
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

IScene* SceneGame::manageInput()
{
  IInputManagerSFML* im = SceneManager::getInstance()->getInputManager();

  // TODO: send cmd to server
  // TODO: we might want to be able to quit or return to menu.
  Protocol::cmd_client c;
  memset(&c, 0, sizeof(c));

  if (im->getKeyStatus(sf::Keyboard::Key::Up).y == true)
    {
      c.top = true;
      std::cout << "Up !" << std::endl;
    }
  if (im->getKeyStatus(sf::Keyboard::Key::Down).y == true)
    {
      c.down = true;
      std::cout << "Down !" << std::endl;
    }
  if (im->getKeyStatus(sf::Keyboard::Key::Left).y == true)
    {
      c.left = true;
      std::cout << "Left !" << std::endl;
    }
  if (im->getKeyStatus(sf::Keyboard::Key::Right).y == true)
    {
      c.right = true;
      std::cout << "Right !" << std::endl;
    }
  if (im->getKeyStatus(sf::Keyboard::Key::Space).y == true)
    {
      // network->Fire();
    }
  if (im->getKeyStatus(sf::Keyboard::Key::Escape).y == true)
    return new SceneHoverConfirmLeave(*this);
  // network->Move(&c);
  return this;
}
