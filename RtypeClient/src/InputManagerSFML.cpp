#include "InputManagerSFML.h"


InputManagerSFML::InputManagerSFML(void)
{
	// well, ok, the enums might not be successive, but come on..
	for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
		keys[(sf::Keyboard::Key)i] = Vector2<bool>(false, false);
}

InputManagerSFML::~InputManagerSFML(void)
{
}

void InputManagerSFML::update()
{
	for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
	{
		Vector2<bool>& v(keys[(sf::Keyboard::Key)i]);
		
		v.x = v.y;
		v.y = isKeyPressed((sf::Keyboard::Key)i);
	}
}

bool InputManagerSFML::isKeyPressed(sf::Keyboard::Key key) const
{
	return sf::Keyboard::isKeyPressed(key);
}

const Vector2<bool>& InputManagerSFML::getKeyStatus(sf::Keyboard::Key k) const
{
	return keys.at(k);
}