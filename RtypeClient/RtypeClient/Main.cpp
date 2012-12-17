#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Coucou");
	while (Window.isOpen())
	{
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			default:
				break;
			}
		}
		Window.clear(sf::Color(0, 255, 255));
		Window.display();
	}
	return 0;
}