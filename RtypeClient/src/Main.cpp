#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GraphicsManagerSFML.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneHoverMenu.h"
#include "SceneBackground.h"
#include <thread>

#include <sstream>
#include <string>


int main()
{
  SceneManager* sm = SceneManager::getInstance();
  sf::Clock timer;
  // INFO: this is the base scene background, you can then decorate it with the appropriate scene. (or change it entirely of course)
  SceneBackground* sb = new SceneBackground();

  sm->changeScene(new SceneHoverMenu(*sb));

  bool isRunning = true;
  
  float imgPerSecond = 0;
  float timeTotal = 0;
  std::string lastFPS;

  while (isRunning)
    {
#define LOOP_UPDATE_DRAW 16
      // FIXME: use real milliseconds..
      if (timer.getElapsedTime().asMilliseconds() > LOOP_UPDATE_DRAW) // around 60 updates and draw per second
	{
	  imgPerSecond += 1;
	  timeTotal += timer.getElapsedTime().asMilliseconds();
	  if (timeTotal >= 1000)
	    {
	      std::ostringstream oss;
	      
	      oss << timeTotal / (timeTotal / imgPerSecond);
	      lastFPS = oss.str();
	      imgPerSecond = 0;
	      timeTotal = 0;
	    }
	  // std::cout << "update: " << timer.getElapsedTime().asMilliseconds() << std::endl;
	  
	  sm->update(timer.getElapsedTime().asMilliseconds());
	  timer.restart();
	  sm->getGraphicsManager()->clear();
	  sm->draw();
	  ValueDrawer d;
	  d.position.y = 580;
	  sm->getGraphicsManager()->write(lastFPS, d);
	  sm->getGraphicsManager()->display();
	  
	}
      std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_UPDATE_DRAW - timer.getElapsedTime().asMilliseconds()));
    }
  return 0;
}
