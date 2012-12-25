#pragma once

#include "IScene.h"
#include "IGraphicsManager.h"
#include "GraphicsManagerSFML.h" // FIXME: That's hard coded... :(

class SceneManager
{
public:
	~SceneManager(void);
	static SceneManager* getInstance();

	//getInputManager();
	void draw();
	void update(float milliseconds);
	void changeScene(IScene* newScene);
	IScene* getCurrentScene();
	IGraphicsManager* getGraphicsManager();
private:
	SceneManager();
	static SceneManager* instance;
	
	IScene* current;
	IGraphicsManager* graphicManager;
};

