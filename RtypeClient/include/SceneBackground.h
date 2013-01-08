#pragma once
#include "IScene.h"
#include "SceneManager.h"
#include "Drawable.h"

class SceneBackground :
	public IScene
{
public:
	SceneBackground(void);
	~SceneBackground(void);
	IScene* update(float elapsedTime);
	void draw();
	void load();
	void unload();
	void setToBackground();
	void setToForeground();
private:
	// TODO: put all the backgrounds in a LayerDrawable (implement LayerDrawable too :D )
	Drawable fixedBackground;
	Drawable scrollingBackground;
	Drawable scrollingBackground2;
};

