#include "SceneBackground.h"


SceneBackground::SceneBackground(void) : fixedBackground(SpriteSheetFactory::getInstance()->getSpriteSheet(1)->getFilename(), Rectangle<int>(1599, 599))
{
  //std::cout << "scenegame construct" << std::endl;
  
  // fixedBackground.setSpriteSheet(SpriteSheetFactory::getInstance()->getSpriteSheet(1));
  //std::cout << "scenegame multiple construct" << std::endl;
  // fixedBackground.setPosition(0, 0);
  //std::cout << "scenegame after setposition" << std::endl;
  // fixedBackground.animate(0);
  //std::cout << "scenegame END construct" << std::endl;

  scrollingBackground.setSpriteSheet(SpriteSheetFactory::getInstance()->getSpriteSheet(2));
  //std::cout << "scenegame multiple construct" << std::endl;
  scrollingBackground.setPosition(0, 0);
  //std::cout << "scenegame after setposition" << std::endl;
  scrollingBackground.animate(0);

  scrollingBackground._manual_next_frame();
  //std::cout << "scenegame END construct" << std::endl;

  scrollingBackground2.setSpriteSheet(SpriteSheetFactory::getInstance()->getSpriteSheet(2));
  //std::cout << "scenegame multiple construct" << std::endl;
  scrollingBackground2.setPosition(0, 0);
  //std::cout << "scenegame after setposition" << std::endl;
  scrollingBackground2.animate(0);
  //std::cout << "scenegame END construct" << std::endl;
}


SceneBackground::~SceneBackground(void)
{
}

IScene* SceneBackground::update(float elapsedTime)
{
  fixedBackground.update(elapsedTime);
  scrollingBackground.update(elapsedTime);
  scrollingBackground2.update(elapsedTime);
  return this;
}

void SceneBackground::draw()
{
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();
  gm->draw(&fixedBackground);
  std::cout << "drawing" << std::endl;
  gm->draw(&scrollingBackground);
  gm->draw(&scrollingBackground2);
}

void SceneBackground::load()
{

}

void SceneBackground::unload()
{

}

void SceneBackground::setToBackground()
{

}

void SceneBackground::setToForeground()
{

}
