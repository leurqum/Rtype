#pragma once

#include <map>

#include "SpriteSheet.h"

// TODO: use friend attribute for SpriteSheet constructor so we are to use the factory.


// TODO: put more consts but i'm lazy right now...

class SpriteSheetFactory
{
 public:
  static SpriteSheetFactory* getInstance();
  SpriteSheet* getSpriteSheet(int);

 private:
  SpriteSheetFactory();
  static SpriteSheetFactory* instance;
  std::map<int, SpriteSheet*> spriteSheets;
};
