#pragma once

#include <sstream>

#include "ASceneHover.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "DrawerMenu.h"
#include "Network.h"

#include "SceneBackground.h"

class SceneListGame :
	public ASceneHover
{
public:
  SceneListGame(IScene& decoratedScene, Network*);
	~SceneListGame(void);

	virtual IScene* update(float elapsedTime);
	virtual void draw();
	virtual void load();
	virtual void unload();
	virtual void setToBackground();
	virtual void setToForeground();
	void refreshGames();
private:
	DrawerMenu menuGames;
	std::list<Protocol::party> games;
	Network* network;
};

