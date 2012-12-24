#pragma once

#include <list>
#include <map>

#include "IDrawable.h"
#include "../../Protocol.h"

class IGraphicsManager
{
public:
	virtual void reset() = 0;
	virtual void addDrawableToScene(const IDrawable& drawable) = 0;
	virtual void draw() = 0;
	virtual IDrawable* createDrawableFrom( const Protocol::drawable& d) = 0;
	virtual void deleteDrawable(const IDrawable*) = 0;
};