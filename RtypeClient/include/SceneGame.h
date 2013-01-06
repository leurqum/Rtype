#pragma once

#include "IScene.h"

#include "DrawableRemote.h"
#include "SceneManager.h"
#include "../../protocol.h"

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
	DrawableRemote* ship[4]; // these are drawables updatable from a protocol::drawable.
};

