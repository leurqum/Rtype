#include "SpriteSheetFactory.h"

#include <iostream>

SpriteSheetFactory::SpriteSheetFactory()
{
  // FIXME: all these spriteSheets are leaked. OK, it doesn't matter as it's a singleton, but if we want to free some resource at runtime, make sure to fix this.
 
  // SHIPS spritesheet
   spriteSheets[0] = new SpriteSheet();
  spriteSheets[0]->setFilename("sprites/r-typesheet42.gif");

  std::map<int, Animation<ValueDrawable>* > animList;
  std::list<ValueDrawable > singleAnim;
  singleAnim.push_back(ValueDrawable(33, 17, 0, 0));
  singleAnim.push_back(ValueDrawable(33, 17, 33, 0));
  singleAnim.push_back(ValueDrawable(33, 17, 66, 0));
  singleAnim.push_back(ValueDrawable(33, 17, 99, 0));
  singleAnim.push_back(ValueDrawable(33, 17, 132, 0));
  singleAnim.push_back(ValueDrawable(33, 17, 99, 0));
  singleAnim.push_back(ValueDrawable(33, 17, 66, 0));
  singleAnim.push_back(ValueDrawable(33, 17, 33, 0));
  // singleAnim.push_back({{33, 17}, {0, 0}});
  animList[0] = new Animation<ValueDrawable>(singleAnim, 250, false);

  singleAnim.clear();
  singleAnim.push_back(ValueDrawable(33, 17, 0, 17));
  singleAnim.push_back(ValueDrawable(33, 17, 33, 17));
  singleAnim.push_back(ValueDrawable(33, 17, 66, 17));
  singleAnim.push_back(ValueDrawable(33, 17, 99, 17));
  singleAnim.push_back(ValueDrawable(33, 17, 132, 17));
  singleAnim.push_back(ValueDrawable(33, 17, 99, 17));
  singleAnim.push_back(ValueDrawable(33, 17, 66, 17));
  singleAnim.push_back(ValueDrawable(33, 17, 33, 17));
  animList[1] = new Animation<ValueDrawable>(singleAnim, 250, false);
  spriteSheets[0]->setAnimations(animList);
  //

  // Background fixed image
  animList.clear();
  singleAnim.clear();
  singleAnim.push_back(ValueDrawable(1599, 599, 0, 0));
  animList[0] = new Animation<ValueDrawable>(singleAnim, 250, false);
  // std::cout << v.position.x << std::endl;
  // std::cout << v.position.y << std::endl;
  // std::cout << "mmh"<<std::endl;
  spriteSheets[1] = new SpriteSheet();
  spriteSheets[1]->setFilename("sprites/farback.gif");
  spriteSheets[1]->setAnimations(animList);
  //

  // Background scrolling image
  animList.clear();
  singleAnim.clear();

  spriteSheets[2] = new SpriteSheet();
  spriteSheets[2]->setFilename("sprites/starfield.png");
  singleAnim.push_back(ValueDrawable(799, 599, -799, 0));
  singleAnim.push_back(ValueDrawable(799, 599, 0, 0));
  singleAnim.push_back(ValueDrawable(799, 599, 799, 0));
  animList[0] = new Animation<ValueDrawable>(singleAnim, 10000, true);
  spriteSheets[2]->setAnimations(animList);
  //


  // [------- UI -------]

  // UI buttons
  animList.clear();
  singleAnim.clear();

  spriteSheets[3] = new SpriteSheet();
  spriteSheets[3]->setFilename("sprites/button_default.png");
  singleAnim.push_back(ValueDrawable(141, 27, 0, 0));
  animList[0] = new Animation<ValueDrawable>(singleAnim, 250, false);
  singleAnim.clear();
  // TODO: add [selected] "animation" (proper to default) (it's just an image, but c'm'on, better than nothing)
  singleAnim.push_back(ValueDrawable(141, 29, 0, 55));
  animList[1] = new Animation<ValueDrawable>(singleAnim, 250, false);

  spriteSheets[3]->setAnimations(animList);
  //
  
  //UI arrows
  animList.clear();
  singleAnim.clear();

  spriteSheets[4] = new SpriteSheet();
  spriteSheets[4]->setFilename("sprites/arrows.png");
  singleAnim.push_back(ValueDrawable(23, 26, 0, -1));
  singleAnim.push_back(ValueDrawable(23, 26, 0, 47));
  animList[0] = new Animation<ValueDrawable>(singleAnim, 800, false);
  
  spriteSheets[4]->setAnimations(animList);
  //


  // ENEMY BASIC  
  spriteSheets[5] = new SpriteSheet();
  spriteSheets[5]->setFilename("sprites/r-typesheet5.gif");

  singleAnim.clear();
  singleAnim.push_back(ValueDrawable(28, 36, 0, 0));

  singleAnim.push_back(ValueDrawable(28, 36, 33, 0));
  singleAnim.push_back(ValueDrawable(28, 36, 68, 0));
  singleAnim.push_back(ValueDrawable(28, 36, 100, 0));
  singleAnim.push_back(ValueDrawable(28, 36, 133, 0));
  singleAnim.push_back(ValueDrawable(28, 36, 165, 0));
  singleAnim.push_back(ValueDrawable(28, 36, 200, 0));

  singleAnim.push_back(ValueDrawable(28, 36, 232, 0));

  animList[0] = new Animation<ValueDrawable>(singleAnim, 250, false);
  spriteSheets[5]->setAnimations(animList);

  // BAR CONTAINER  
  spriteSheets[6] = new SpriteSheet();
  spriteSheets[6]->setFilename("sprites/bar_hp_mp.png");

  singleAnim.clear();

  singleAnim.push_back(ValueDrawable(106, 32, 0, 32));

  animList[0] = new Animation<ValueDrawable>(singleAnim, 250, false);
  spriteSheets[6]->setAnimations(animList);
  
  // BULLETS BASIC
  spriteSheets[7] = new SpriteSheet();
  spriteSheets[7]->setFilename("sprites/r-typesheet1.gif");

  singleAnim.clear();

  singleAnim.push_back(ValueDrawable(18, 18, 230, 101));
  singleAnim.push_back(ValueDrawable(18, 18, 249, 101));

  animList[0] = new Animation<ValueDrawable>(singleAnim, 250, false);

  singleAnim.clear();

  singleAnim.push_back(ValueDrawable(18, 18, 266, 101));
  singleAnim.push_back(ValueDrawable(18, 18, 284, 101));

  animList[1] = new Animation<ValueDrawable>(singleAnim, 250, false);
  spriteSheets[7]->setAnimations(animList);

  // EXPLOSION

  spriteSheets[8] = new SpriteSheet();
  spriteSheets[8]->setFilename("sprites/r-typesheet43.gif");

  singleAnim.clear();

  singleAnim.push_back(ValueDrawable(20, 20, 0, 78));
  singleAnim.push_back(ValueDrawable(29, 25, 27, 55));
  singleAnim.push_back(ValueDrawable(34, 30, 62, 54));
  singleAnim.push_back(ValueDrawable(35, 32, 96, 53));
  singleAnim.push_back(ValueDrawable(34, 31, 131, 53));
  singleAnim.push_back(ValueDrawable(34, 31, 131, 53));
  singleAnim.push_back(ValueDrawable(34, 32, 166, 53));

  animList[0] = new Animation<ValueDrawable>(singleAnim, 100, false);

  spriteSheets[8]->setAnimations(animList);

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
