#pragma once

#include "IDrawable.h"

class IGraphicsManager
{
public:
	virtual void reset() = 0;
	virtual void addDrawableToScene(const IDrawable& drawable) = 0;
	virtual void draw() = 0;
	virtual IDrawable* createDrawableFrom( /* this would take a protocol drawable as parameter */ ) = 0;
	virtual void deleteDrawable(const IDrawable*) = 0;
};