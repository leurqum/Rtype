#pragma once

#include "ASceneHover.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "DrawerMenu.h"
#include "SceneListGame.h"
#include "SceneHoverConfirmLeave.h"
#include "Network.h"

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
	DrawerMenu menu;
	enum BgState
	{
	  FOREGROUND,
	  BACKGROUND,
	  TO_FOREGROUND,
	  TO_BACKGROUND
	};
	BgState isBackground;
};

