#pragma once

#include <string.h>
#include <map>
#include "IInputManagerSFML.h"

class InputManagerSFML
	: public IInputManagerSFML
{
public:
	InputManagerSFML(void);
	~InputManagerSFML(void);

	virtual void		update(); // we don't need time here.
	bool isKeyPressed(sf::Keyboard::Key) const;
	virtual const Vector2<bool>& getKeyStatus(sf::Keyboard::Key) const;
private:
	std::map<sf::Keyboard::Key, Vector2<bool> > keys;
};

