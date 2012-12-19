#pragma once
#include <list>
#include <map>

#include "IDrawable.h"

class Drawable :
	public IDrawable
{
private:
	Rectangle<int>* rectSource;
	std::string spriteFilename;
	std::map<int, std::list<Rectangle<int>>> animationList;
public:

	Drawable(void);
	~Drawable(void);

	Vector2<float> getPosition() const;
	const std::string& getSpriteSheetFilename() const;
	const Rectangle<int>& getRectSpriteSheet() const;
	bool animate(int idAnimation);
	void update(float elapsedTime);
};

