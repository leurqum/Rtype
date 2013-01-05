#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GraphicsManagerSFML.h"
#include "SceneManager.h"
#include "SceneGame.h"

int main()
{
  SceneManager* sm = SceneManager::getInstance();
  sf::Clock timer;

  sm->changeScene(new SceneGame());

  bool isRunning = true;
  while (isRunning)
    {
      // FIXME: use real milliseconds..
      if (timer.getElapsedTime().asMilliseconds() > 166) // around 60 updates and draw per second
	{
	  std::cout << "update" << std::endl;
	  sm->update(timer.getElapsedTime().asMilliseconds());
	  timer.restart();
	  sm->getGraphicsManager()->clear();
	  sm->draw();
	  sm->getGraphicsManager()->display();
	}
    }
  return 0;
}
