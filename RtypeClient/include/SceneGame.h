#pragma once

#include "IScene.h"
#include "ASceneHover.h"

#include "Drawable.h"
#include "DrawableGeneric.h"
#include "DrawerDrawable.h"
#include "SceneManager.h"
#include "../../protocol.h"

#include "DrawerShip.h"
#include "DrawerEnemyBasic.h"

class SceneGame :
public ASceneHover
{
 public:
  SceneGame(IScene&);
  ~SceneGame(void);
  IScene* update(float elapsedTime);
  void draw();
  void load();
  void unload();
  void setToBackground();
  void setToForeground();
 private:
  // FIXME: remake this updatable. (specialize it)
  DrawerShip* ship[4]; // these are drawables updatable from a protocol::drawable.
  DrawerEnemyBasic enemy;
  // TODO: put all the backgrounds in a LayerDrawable (implement LayerDrawable too :D )
  //Drawable fixedBackground;
  //Drawable scrollingBackground;
  //Drawable scrollingBackground2;
};

