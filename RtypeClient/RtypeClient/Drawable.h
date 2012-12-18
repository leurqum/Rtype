#pragma once
#include <list>
#include <map>

#include "IDrawable.h"

class Drawable :
	public IDrawable
{
private:
	Rectangle* rectSource;
	std::string spriteFilename;
	std::map<int, std::list<Rectangle>> animationList;
public:

	Drawable(void);
	~Drawable(void);

	Vector2f getPosition() const;
	const std::string& getSpriteSheetFilename() const;
	const Rectangle& getRectSpriteSheet() const;
	bool animate(int idAnimation);
	void update(float elapsedTime);
};

