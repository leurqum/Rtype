#include "SpriteSheetFactory.h"

SpriteSheetFactory::SpriteSheetFactory()
{
  spriteSheets[0] = new SpriteSheet();
  spriteSheets[0]->setFilename("sprites/r-typesheet42.gif");

  std::map<int, std::list<Rectangle<int> > > animList;
  std::list<Rectangle<int> > singleAnim;
  singleAnim.push_back(Rectangle<int>(33, 17));
  singleAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(132, 0)));
  animList[0] = singleAnim;

  singleAnim.clear();
  singleAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(0, 17)));
  singleAnim.push_back(Rectangle<int>(33, 17, Vector2<int>(132, 17)));
  animList[1] = singleAnim;
  spriteSheets[0]->setAnimations(animList);
  spriteSheets[0]->setInterpolation(4);
  
}

SpriteSheetFactory* SpriteSheetFactory::instance = nullptr;

SpriteSheetFactory* SpriteSheetFactory::getInstance()
{
  if (instance == nullptr)
    instance = new SpriteSheetFactory();
  return instance;
}

SpriteSheet* SpriteSheetFactory::getSpriteSheet(int id)
{
  return spriteSheets[id];
}
