#pragma once

#include "IScene.h"
#include "SceneManager.h"
#include "DrawableGeneric.h"
#include "DrawerDrawable.h"
#include "FactoryDrawable.h"

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
	DrawableGeneric* fixedBackground;
	DrawerDrawable _fixedBackground;
	DrawableGeneric* scrollingBackground;
	DrawerDrawable _scrollingBackground;
	DrawableGeneric* scrollingBackground2;
	DrawerDrawable _scrollingBackground2;
};

