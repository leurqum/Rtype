#pragma once

#include <list>
#include <map>

#include "SceneManager.h"
#include "IDrawable.h"
#include "SpriteSheet.h"
#include "SpriteSheetFactory.h"

#include "../../protocol.h"

#include "Rectangle.h"

// TODO: rename in "RemoteDrawable" or smth like that.

class Drawable :
	public IDrawable
{
private:
	int animationId;
	std::list< Rectangle<int> >::const_iterator* currentRect;
	Vector2<float> position;

	const SpriteSheet* spriteSheet;
	Protocol::drawable* updater;
public:

	Drawable();
	~Drawable(void);

	Vector2<float> getPosition() const;
	void setPosition(float x, float y);
	const SpriteSheet* getSpriteSheet() const;
	const Rectangle<int>& getRectSpriteSheet() const;
	bool animate(int idAnimation);
	void update(float elapsedTime);

	// The next update will take d as parameter, and we assume it has been received just after last update. (actually, there's a fair chance that we got it some time later, but with the network delay, if we simulate its movement, it would improve the instantaneity, but decrease rightfulness / we might see some jumping assets on extreme ping (high or low))
	void setUpdate(const Protocol::drawable& d);
};

