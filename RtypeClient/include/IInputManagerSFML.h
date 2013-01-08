#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

// en cas d implementation de joystick
// #include <SFML/Window/Joystick.hpp>

#include "Vector2.h"

class IInputManagerSFML
{
public:
	virtual void		update() = 0; // we don't need time here.

	virtual bool		isKeyPressed(sf::Keyboard::Key) const = 0;
	virtual const Vector2<bool>& getKeyStatus(sf::Keyboard::Key) const = 0;
};