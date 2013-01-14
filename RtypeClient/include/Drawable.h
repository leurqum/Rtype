#pragma once

#include <string>

#include "Modifiable.h"
#include "ValueDrawable.h"

class Drawable : public Modifiable<ValueDrawable>
{
 public:
  Drawable(const std::string& spriteSheet);
  Drawable(const std::string& spriteSheet, const ValueDrawable&);
  const std::string& getSpriteSheetFilename() const;
 private:
  const std::string spriteSheetFilename; // we copy it because we might not want to store that filename in another lcation (it was ref before.)
};
