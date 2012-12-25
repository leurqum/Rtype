#include "InputManagerSFML.h"


InputManagerSFML::InputManagerSFML(void)
{
}

InputManagerSFML::~InputManagerSFML(void)
{
}

bool InputManagerSFML::isKeyPressed(sf::Keyboard::Key key)
{
	return sf::Keyboard::isKeyPressed(key);
}
