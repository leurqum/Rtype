#pragma once

#include "ASceneHover.h"
#include "SceneManager.h"
#include "SceneGame.h"

class SceneHoverMenu :
	public ASceneHover
{
public:
	SceneHoverMenu(IScene& decoratedScene);
	~SceneHoverMenu(void);

	virtual IScene* update(float elapsedTime);
	virtual void draw();
	virtual void load();
	virtual void unload();
	virtual void setToBackground();
	virtual void setToForeground();
private:
	Drawable playButton;
	Drawable searchGameButton;
	Drawable selectionArrow;
};

