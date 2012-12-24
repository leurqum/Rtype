#pragma once

#include <list>
#include <map>

#include "IDrawable.h"
#include "SpriteSheet.h"

#include "../../protocol.h"

class Drawable :
	public IDrawable
{
private:
	int animationId;
	int animationPosition;
	Vector2<float> position;

	const SpriteSheet& spriteSheet;
public:

	Drawable(const SpriteSheet&);
	~Drawable(void);

	Vector2<float> getPosition() const;
	const std::string& getSpriteSheetFilename() const;
	const Rectangle<int>& getRectSpriteSheet() const;
	bool animate(int idAnimation);
	void update(float elapsedTime);
};

