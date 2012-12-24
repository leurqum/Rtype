#pragma once

#include <list>
#include <map>
#include <string>

#include "Rectangle.h"

class SpriteSheet
{
public:
	std::string filename;
	std::map<int, std::list<Rectangle<int> > > animations;

	SpriteSheet(void);
	~SpriteSheet(void);
};