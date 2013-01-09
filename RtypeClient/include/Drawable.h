#pragma once

#include <list>
#include <map>


#include "SpriteSheet.h"
#include "SpriteSheetFactory.h"
#include "Animation.h"

#include "../../protocol.h"

#include "Rectangle.h"

#include "SimpleDrawable.h"
#include "DrawerModifiable.h"

// TODO: rename in "RemoteDrawable" or smth like that.

class Drawable :
virtual public SimpleDrawable
{
protected:
	Animation::Iterator* rectIterator;
	const SpriteSheet* spriteSheet;
	
public:

	Drawable(const SpriteSheet& ss);
	~Drawable(void);

	virtual const std::string& getSpriteSheet() const;
	virtual const Rectangle<int>* getRectSpriteSheet() const;

	// This will influence on the rectSpriteSheet returned.
	virtual bool animate(int idAnimation);

	virtual void update(float elapsedTime);

	// encapsulated Low level control on the drawable.
	virtual void _manual_next_frame();
};

