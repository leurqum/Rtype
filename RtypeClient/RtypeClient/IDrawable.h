#pragma once

#include <iostream>
#include "Rectangle.h"
#include "Vector2f.h"

class IDrawable
{
public:
	virtual Vector2f getPosition() const = 0;
	virtual const std::string& getSpriteSheetFilename() const = 0;
	virtual const Rectangle& getRectSpriteSheet() const = 0;
	virtual bool animate(int idAnimation) = 0;
	virtual void update(float elapsedTime) = 0;
};