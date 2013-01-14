#pragma once

#include "ASceneHover.h"
#include "SceneManager.h"
#include "SceneGame.h"
#include "DrawerMenu.h"
#include "SceneListGame.h"

class SceneHoverConfirmLeave :
	public ASceneHover
{
public:
  SceneHoverConfirmLeave(IScene& decoratedScene, bool homeLink = true);
  ~SceneHoverConfirmLeave(void);
  
  virtual IScene* update(float elapsedTime);
  virtual void draw();
  virtual void load();
  virtual void unload();
  virtual void setToBackground();
  virtual void setToForeground();
 private:
	DrawerMenu menu;
};
