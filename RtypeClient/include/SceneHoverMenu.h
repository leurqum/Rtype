#pragma once

#include "ASceneHover.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "LayerDrawable.h"


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
	LayerDrawable allButtons;
	Drawable playButton;
	Drawable exitButton;
	Drawable selectionArrow;
	int selectionPosition;
	int nbButtons;
	Vector2<float> firstSelection;
	Vector2<float> gapButtons;
};

