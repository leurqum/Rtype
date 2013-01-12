#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GraphicsManagerSFML.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneHoverMenu.h"
#include "SceneBackground.h"
#include <thread>

int main()
{
  SceneManager* sm = SceneManager::getInstance();
  sf::Clock timer;
  // INFO: this is the base scene background, you can then decorate it with the appropriate scene. (or change it entirely of course)
  SceneBackground* sb = new SceneBackground();

  sm->changeScene(new SceneHoverMenu(*sb));

  bool isRunning = true;
  while (isRunning)
    {
#define LOOP_UPDATE_DRAW 16
      // FIXME: use real milliseconds..
      if (timer.getElapsedTime().asMilliseconds() > LOOP_UPDATE_DRAW) // around 60 updates and draw per second
	{
	  std::cout << "update: " << timer.getElapsedTime().asMilliseconds() << std::endl;
	  sm->update(timer.getElapsedTime().asMilliseconds());
	  timer.restart();
	  sm->getGraphicsManager()->clear();
	  sm->draw();
	  sm->getGraphicsManager()->display();
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_UPDATE_DRAW - timer.getElapsedTime().asMilliseconds()));
    }
  return 0;
}
