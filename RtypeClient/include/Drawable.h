#pragma once

#include <list>
#include <map>

#include "IDrawable.h"
#include "SpriteSheet.h"

#include "../../protocol.h"

#include "Rectangle.h"

class Drawable :
	public IDrawable
{
private:
	int animationId;
	std::list< Rectangle<int> >::const_iterator currentRect;
	Vector2<float> position;

	const SpriteSheet& spriteSheet;
public:

	Drawable(const SpriteSheet&);
	~Drawable(void);

	Vector2<float> getPosition() const;
	void setPosition(float x, float y);
	const std::string& getSpriteSheetFilename() const;
	const Rectangle<int>& getRectSpriteSheet() const;
	bool animate(int idAnimation);
	void update(float elapsedTime);
};

