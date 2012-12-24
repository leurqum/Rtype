
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

// en cas d implementation de joystick
// #include <SFML/Window/Joystick.hpp>

class IInputManagerSFML
{
public:
	virtual bool		isKeyPressed(sf::Keyboard::Key) = 0;
};