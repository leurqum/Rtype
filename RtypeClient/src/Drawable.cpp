#include "Drawable.h"

Drawable::Drawable(const std::string& spriteSheet) : spriteSheetFilename(spriteSheet)
{

}

Drawable::Drawable(const std::string& spriteSheet, const ValueDrawable& v) : Modifiable(v), spriteSheetFilename(spriteSheet)
{

}

const std::string& Drawable::getSpriteSheetFilename() const
{
  return spriteSheetFilename;
}
