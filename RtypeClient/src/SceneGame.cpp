#include "SceneGame.h"


SceneGame::SceneGame(void)
{
	Protocol::drawable d;
	d.id = 0;
	d.type = Protocol::SHIP;
	d.xPosition = 123;
	d.yPosition = 123;
	IDrawable* drawable = SceneManager::getInstance()->getGraphicsManager()->createDrawableFrom(d);
	ship = drawable;
}


SceneGame::~SceneGame(void)
{
}

IScene* SceneGame::update(float elapsedTime)
{
	// TODO: update background scenes ?
	
	// TODO: update the scene depending on network data received.

	// TODO: insert input managing code here.

	// NOTE: the GraphicsManager will take care of the animations
	SceneManager::getInstance()->getGraphicsManager()->update(elapsedTime);
	return this;
}

void SceneGame::draw()
{
	SceneManager::getInstance()->getGraphicsManager()->draw();
}

void SceneGame::load()
{

}

void SceneGame::unload()
{

}

void SceneGame::setToBackground()
{

}

void SceneGame::setToForeground()
{

}