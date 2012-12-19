#include <SFML/Graphics.hpp>
#include "GraphicsManagerSFML.h"

int main()
{
	IGraphicsManager* graphManager = GraphicsManagerSFML::getInstance();

	bool isRunning = true;
	while (isRunning)
	{
		graphManager->draw();
	}
	return 0;
}