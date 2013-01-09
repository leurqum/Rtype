#pragma once

#include <list>
#include <map>


#include "SimpleDrawable.h"
#include "SpriteSheet.h"
#include "SpriteSheetFactory.h"
#include "Animation.h"

#include "../../protocol.h"

#include "Rectangle.h"
#include "IDrawer.h"

// TODO: rename in "RemoteDrawable" or smth like that.

class Drawable :
public SimpleDrawable, virtual public IDrawer
{
protected:
	Animation::Iterator* rectIterator;
	Vector2<float> position;
	const SpriteSheet* spriteSheet;
	std::list<Animation::Iterator> modifiers;
	
public:

	Drawable(const SpriteSheet& ss);
	~Drawable(void);

	Vector2<float> getPosition() const;
	virtual void setPosition(float x, float y);
	virtual const std::string& getSpriteSheet() const;
	virtual const Rectangle<int>* getRectSpriteSheet() const;

	virtual void drawTo(IGraphicsManager*) const;

	// This will influence on the rectSpriteSheet returned.
	virtual bool animate(int idAnimation);

	// TODO: make another class with just this, inheriting from a base class more generic than Drawable.
	// This will influence on the position, will be applied after current finishes.
	// TODO: make animations for rotation/scale/etc...
	// put this in Drawer ? YES.
	virtual void addModifier(const Animation& a);
	// TODO: add popModifier ?


	virtual void update(float elapsedTime);

	// encapsulated Low level control on the drawable.
	virtual void _manual_next_frame();
};

