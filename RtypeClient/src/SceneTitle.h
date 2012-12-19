#pragma once
#include "IScene.h"

class SceneTitle :
	public IScene
{
public:
	SceneTitle(void);
	~SceneTitle(void);
	IScene* update(float elapsedTime);
	void draw();
	void load();
	void unload();
	void setToBackground();
	void setToForeground();
};

