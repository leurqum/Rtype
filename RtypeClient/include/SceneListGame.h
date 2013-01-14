#pragma once

#include "ASceneHover.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "DrawerMenu.h"

#include "SceneBackground.h"

class SceneListGame :
	public ASceneHover
{
public:
	SceneListGame(IScene& decoratedScene);
	~SceneListGame(void);

	virtual IScene* update(float elapsedTime);
	virtual void draw();
	virtual void load();
	virtual void unload();
	virtual void setToBackground();
	virtual void setToForeground();
private:
	DrawerMenu menuGames;
};

