#include "SceneGame.h"

SceneGame::SceneGame(IScene& decoratedScene, Network* net) :
	ASceneHover(decoratedScene), network(net)
{
  ship[0] = nullptr;
  ship[1] = nullptr;
  ship[2] = nullptr;
  ship[3] = nullptr;
  drawer_2bars.setBar1(100);
  enemy.push_back(DrawerEnemyBasic());
  Protocol::drawable d;
  d.xPosition = 150;
  d.yPosition = 150;
  d.id = -1;
  d.type = Protocol::type_drawable::ENEMY_EASY;
  enemy.back().setUpdate(d);
  bullets.push_back(DrawerBullet());
  d.xPosition += 30;
  bullets.back().setUpdate(d);
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
      // std::cout << "new update !" << std::endl;
      // std::cout << "received: " << recved << std::endl;
      if (recved && d.type == Protocol::type_drawable::SHIP)
	{
	  // TODO: find right ship.
	  // std::cout << "i'ts a ship !" << std::endl;
	  // std::cout << d.xPosition << ";" << d.yPosition << std::endl;
	  if (ship[0] == nullptr)
	    {
	      ship[0] = new DrawerShip(0);
	    }
	  ship[0]->setUpdate(d);
	}
      else if (recved && d.type == Protocol::type_drawable::ENEMY_EASY)
	{
	  bool found = false;
	  // seek right enemy
	  for (DrawerEnemyBasic& e : enemy)
	    {
	      if (e.getId() == d.id)
		{
		  std::cout << "update enemy: " << d.xPosition << ";" << d.yPosition << std::endl;
		  e.setUpdate(d);
		  found = true;
		}
	    }
	  if (!found)
	    {
	      std::cout << "NEW Enemy ! " << d.xPosition << ";" << d.yPosition << std::endl;
	      //create new enemy
	      enemy.push_back(DrawerEnemyBasic());
	      enemy.back().setUpdate(d);
	    }
	}
      else if (recved && d.type == Protocol::type_drawable::BULLET_LINEAR)
	{
	  bool found = false;
	  // seek right enemy
	  for (DrawerBullet& b : bullets)
	    {
	      if (b.getId() == d.id)
		{
		  std::cout << "update bullet: " << d.xPosition << ";" << d.yPosition << std::endl;
		  b.setUpdate(d);
		  found = true;
		}
	    }
	  if (!found)
	    {
	      std::cout << "NEW bullet ! " << d.xPosition << ";" << d.yPosition << std::endl;
	      //create new enemy
	      bullets.push_back(DrawerBullet());
	      bullets.back().setUpdate(d);
	    }
	}
    }

  if (ship[0])
    ship[0]->update(elapsedTime);
  for (DrawerEnemyBasic& e : enemy)
    e.update(elapsedTime);
  for (DrawerBullet& b : bullets)
    b.update(elapsedTime);
  drawer_2bars.update(elapsedTime);


  // std::cout << "scenegame END update" << std::endl;
  return manageInput(); // manage input before updates would improve responsiveness if we take it into account for our drawings, but we don't do this for the moment, so it would add unnessecary complexity.
}

void SceneGame::draw()
{
  ASceneHover::draw();


  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();

  for (DrawerBullet& b : bullets)
    b.drawTo(gm);
  for (DrawerEnemyBasic& e : enemy)
    e.drawTo(gm);

  // drawer_2bars.drawTo(gm);
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
