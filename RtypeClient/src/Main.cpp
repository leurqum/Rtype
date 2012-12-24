#include <SFML/Graphics.hpp>
#include "GraphicsManagerSFML.h"

int main()
{
	GraphicsManagerSFML* graphManager = GraphicsManagerSFML::getInstance();

	bool isRunning = true;
	Protocol::drawable d;
	d.id = 0;
	d.type = Protocol::SHIP;
	d.xPosition = 123;
	d.yPosition = 123;

	IDrawable* drawable = graphManager->createDrawableFrom(d);
	
	while (isRunning)
	{
		// FIXME: use real milliseconds..
		graphManager->update(1);
		graphManager->draw();
	}
	return 0;
}