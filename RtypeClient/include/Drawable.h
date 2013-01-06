#pragma once

#include <list>
#include <map>


#include "IDrawable.h"
#include "SpriteSheet.h"
#include "SpriteSheetFactory.h"

#include "../../protocol.h"

#include "Rectangle.h"

// TODO: rename in "RemoteDrawable" or smth like that.

class Drawable :
	public IDrawable
{
protected:
	SpriteSheet::Iterator* rectIterator;
	Vector2<float> position;
	const SpriteSheet* spriteSheet;

public:

	Drawable();
	~Drawable(void);

	Vector2<float> getPosition() const;
	virtual void setPosition(float x, float y);
	virtual const SpriteSheet* getSpriteSheet() const;
	virtual void setSpriteSheet(const SpriteSheet*);
	virtual Rectangle<int> getRectSpriteSheet() const;
	virtual bool animate(int idAnimation);
	virtual void update(float elapsedTime);
};

