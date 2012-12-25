#include <SFML/Graphics.hpp>
#include "GraphicsManagerSFML.h"
#include "SceneManager.h"
#include "SceneGame.h"

int main()
{
	SceneManager* sm = SceneManager::getInstance();

	sm->changeScene(new SceneGame());

	bool isRunning = true;
	while (isRunning)
	{
		// FIXME: use real milliseconds..
		sm->update(1);
		sm->draw();
	}
	return 0;
}