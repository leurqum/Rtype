#include <SFML/Graphics.hpp>
#include "GraphicsManagerSFML.h"

int main()
{
	GraphicsManagerSFML* graphManager = GraphicsManagerSFML::getInstance();

	bool isRunning = true;
	Protocol::drawable d;
	d.id = 0;
	d.type = Protocol::SHIP;
	d.xPosition = 0;
	d.yPosition = 0;

	IDrawable* drawable = graphManager->createDrawableFrom(d);
	while (isRunning)
	{
		graphManager->draw();
	}
	return 0;
}