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
#include "Drawer2Bars.h"
#include "DrawerBullet.h"
#include "SceneHoverMenu.h"
#include "SceneHoverConfirmLeave.h"

#include "Network.h"

class SceneGame :
public ASceneHover
{
 public:
  SceneGame(IScene&, Network*);
  ~SceneGame(void);
  IScene* update(float elapsedTime);
  void draw();
  void load();
  void unload();
  void setToBackground();
  void setToForeground();

  template<typename T>
    void updateList(std::list<T>& l, Protocol::drawable&);
 private:
IScene* manageInput();

 std::list<DrawerShip> ships;
 std::list<DrawerEnemyBasic> enemy;
 std::list<DrawerBullet> bullets;
 Drawer2Bars drawer_2bars;
 Network*		network;
};

