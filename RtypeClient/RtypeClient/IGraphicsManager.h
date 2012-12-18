#pragma once

#include "IDrawable.h"

class IGraphicsManager
{
public:
	virtual void init() = 0;
	virtual void draw(const IDrawable& drawable) = 0;
	virtual void clear() = 0;
	virtual IDrawable* createDrawableFrom( /* this would take a protocol drawable as parameter */ ) = 0;
	virtual void deleteDrawable(const IDrawable*) = 0;
};