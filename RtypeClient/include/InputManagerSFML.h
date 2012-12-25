#pragma once

#include "IInputManagerSFML.h"

class InputManagerSFML
	: public IInputManagerSFML
{
public:
	InputManagerSFML(void);
	~InputManagerSFML(void);

	bool isKeyPressed(sf::Keyboard::Key);
};

