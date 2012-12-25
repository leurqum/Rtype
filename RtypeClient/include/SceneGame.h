#pragma once

#include "IScene.h"
#include "SceneManager.h"
#include "../protocol.h"

class SceneGame :
	public IScene
{
public:
	SceneGame(void);
	~SceneGame(void);
	IScene* update(float elapsedTime);
	void draw();
	void load();
	void unload();
	void setToBackground();
	void setToForeground();
private:
	IDrawable* ship;
};

