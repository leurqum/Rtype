#include "SpriteSheetFactory.h"

SpriteSheetFactory::SpriteSheetFactory()
{
  // SHIPS spritesheet
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
  spriteSheets[0]->setSmoothLoop(true);

  //

  // Background fixed image
  animList.clear();
  singleAnim.clear();

  spriteSheets[1] = new SpriteSheet();
  spriteSheets[1]->setFilename("sprites/farback.gif");
  singleAnim.push_back(Rectangle<int>(1599, 599));
  animList[0] = singleAnim;
  spriteSheets[1]->setAnimations(animList);
  spriteSheets[1]->setInterpolation(1);
  spriteSheets[1]->setSmoothLoop(false);
  //

  // Background scrolling image
  animList.clear();
  singleAnim.clear();

  spriteSheets[2] = new SpriteSheet();
  spriteSheets[2]->setFilename("sprites/starfield.png");
  singleAnim.push_back(Rectangle<int>(799, 599, Vector2<int>(-799, 0)));
  singleAnim.push_back(Rectangle<int>(799, 599, Vector2<int>(799, 0)));
  animList[0] = singleAnim;
  spriteSheets[2]->setAnimations(animList);
  spriteSheets[2]->setInterpolation(400);
  spriteSheets[2]->setSmoothLoop(false);

  //

  // UI buttons
  animList.clear();
  singleAnim.clear();

  spriteSheets[3] = new SpriteSheet();
  spriteSheets[3]->setFilename("sprites/button_default.png");
  singleAnim.push_back(Rectangle<int>(141, 27, Vector2<int>(0, 27)));
  animList[0] = singleAnim;
  // TODO: add [selected] "animation" (it's just an image, but c'm'on, better than nothing)
  spriteSheets[3]->setAnimations(animList);
  spriteSheets[3]->setInterpolation(400);
  spriteSheets[3]->setSmoothLoop(false);

  //
  
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
