#include "SceneGame.h"

SceneGame::SceneGame(IScene& decoratedScene, Network* net) :
  ASceneHover(decoratedScene), network(net)
{
  drawer_2bars.setBar1(0);
  // enemy.push_back(DrawerEnemyBasic());
  // Protocol::drawable d;
  // d.xPosition = 150;
  // d.yPosition = 150;
  // d.id = -1;
  // d.type = Protocol::type_drawable::ENEMY_EASY;
  // enemy.back().setUpdate(d);
  // bullets.push_back(DrawerBullet());
  // d.xPosition += 30;
  // bullets.back().setUpdate(d);
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


  // NOTE: we assume d.type is the right type for old, if it's a wrong type, then it's messed up earlier. (but this class doesn't care, it's Drawable who will handle (or not) the matter.)
  
  bool recved = true;
  int i = 0;
  while (recved && i < 100) // FIXME: it is done so we dont wait forever, but it makes a delay...
    {
      i++;
      Protocol::drawable d = network->GetPieceWorld(recved);
      // Protocol::drawable d;
      // d.type = Protocol::type_drawable::SHIP;
      // static float y = 3;
      // if (y < -1)
      // 	y = 3;
      // d.life = (y -= 0.0002);
      // d.id = 0;
      // d.xPosition = 50;
      // d.yPosition = 50;
      // std::cout << d.life << std::endl;
      // std::cout << "new update !" << std::endl;
      // std::cout << "received: " << recved << std::endl;
      if (recved)
	{
	  if (d.type == Protocol::type_drawable::SHIP)
	    updateList(ships, d);
	  else if (d.type == Protocol::type_drawable::ENEMY_EASY)
	    updateList(enemy, d);
	  else if (d.type == Protocol::type_drawable::BULLET_LINEAR)
	    updateList(bullets, d);
	}
    }

  if (ships.size() > 0)
    drawer_2bars.setBar1(ships.front().getLife() * 100 / 3);
  else
    drawer_2bars.setBar1(0);
  for (DrawerShip& s : ships)
    s.update(elapsedTime);
  for (DrawerEnemyBasic& e : enemy)
    e.update(elapsedTime);
  for (DrawerBullet& b : bullets)
    b.update(elapsedTime);
  drawer_2bars.update(elapsedTime);


  // std::cout << "scenegame END update" << std::endl;
  return manageInput(); // manage input before updates would improve responsiveness if we take it into account for our drawings, but we don't do this for the moment, so it would add unnessecary complexity.
}

template<typename T>
void SceneGame::updateList(std::list<T>& l, Protocol::drawable& d)
{
  // TODO: Use a map ??? (the ship must know its color though. (color might be set at first update...)
  bool found = false;
  // seek right T
  typename std::list<T>::iterator i = l.begin();
  while (i != l.end() && !found)
    {
      if (i->getId() == d.id)
	{
	  found = true;
	}
      else
	i++;
    }

  if (found) // we know the thing
    {
      if (d.life <= 0)
	{
	  l.erase(i);
	  // TODO: create explosion !!!
	}
      else
	i->setUpdate(d);
    }
  else if (d.life > 0) // we don't know it, but no reason to create it if it's dead
    {
      std::cout << "NEW thing ! " << d.xPosition << ";" << d.yPosition << std::endl;
      //create new thing
      l.push_back(T());
      l.back().setUpdate(d);
    }
}

void SceneGame::draw()
{
  ASceneHover::draw();


  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();

  for (DrawerBullet& b : bullets)
    b.drawTo(gm);
  for (DrawerEnemyBasic& e : enemy)
    e.drawTo(gm);

  drawer_2bars.drawTo(gm);
  for (DrawerShip& s : ships)
    s.drawTo(gm);
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
      network->Fire();
    }
  if (im->getKeyStatus(sf::Keyboard::Key::Escape).y == true)
    return new SceneHoverConfirmLeave(*this);
  network->Move(&c);
  return this;
}
