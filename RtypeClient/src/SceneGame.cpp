#include "SceneGame.h"

SceneGame::SceneGame(void)
{
  ship[0] = nullptr;
  ship[1] = nullptr;
  ship[2] = nullptr;
  ship[3] = nullptr;
  
  std::cout << "scenegame construct" << std::endl;
  fixedBackground.setSpriteSheet(SpriteSheetFactory::getInstance()->getSpriteSheet(1));
  std::cout << "scenegame multiple construct" << std::endl;
  fixedBackground.setPosition(0, 0);
  std::cout << "scenegame after setposition" << std::endl;
  fixedBackground.animate(0);
  std::cout << "scenegame END construct" << std::endl;

  scrollingBackground.setSpriteSheet(SpriteSheetFactory::getInstance()->getSpriteSheet(2));
  std::cout << "scenegame multiple construct" << std::endl;
  scrollingBackground.setPosition(0, 0);
  std::cout << "scenegame after setposition" << std::endl;
  scrollingBackground.animate(0);
  // FIXME: this large faked update is resource consuming, we just want to start at half the interpolation...
  scrollingBackground.update(50000);
  std::cout << "scenegame END construct" << std::endl;

  scrollingBackground2.setSpriteSheet(SpriteSheetFactory::getInstance()->getSpriteSheet(2));
  std::cout << "scenegame multiple construct" << std::endl;
  scrollingBackground2.setPosition(0, 0);
  std::cout << "scenegame after setposition" << std::endl;
  scrollingBackground2.animate(0);
  std::cout << "scenegame END construct" << std::endl;

}

SceneGame::~SceneGame(void)
{
}

IScene* SceneGame::update(float elapsedTime)
{
  std::cout << "scenegame update" << std::endl;
  // TODO: (not here but in SceneHoverWhatever) update background scenes ?
	
  // TODO: update the scene depending on network data received.
  Protocol::drawable d;
  d.id = 0;
  d.type = Protocol::SHIP;
  static int x = 490;
  static int incr = 1;

  d.xPosition = x;
   x += incr;
   if (x > 500)
     incr = -5;
   if (x <= 400)
     incr = 5;
  d.yPosition = 123;

  ship[0] = SceneManager::getInstance()->getGraphicsManager()->updateDrawableFrom(ship[0], d);

  // TODO: insert input managing code here.

  ship[0]->update(elapsedTime);
 fixedBackground.update(elapsedTime);
 scrollingBackground.update(elapsedTime);
 scrollingBackground2.update(elapsedTime);
  std::cout << "scenegame END update" << std::endl;
  return this;
}

void SceneGame::draw()
{
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  gm->draw(&fixedBackground);
  std::cout << "drawing" << std::endl;
  gm->draw(&scrollingBackground);
  gm->draw(&scrollingBackground2);
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
