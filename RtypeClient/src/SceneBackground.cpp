#include "SceneBackground.h"


SceneBackground::SceneBackground(void) :
  fixedBackground(FactoryDrawable::getInstance()->createFarBackground()),
  _fixedBackground(*fixedBackground),
  scrollingBackground(FactoryDrawable::getInstance()->createMovingStarsBackground()),
  _scrollingBackground(*scrollingBackground),
  scrollingBackground2(FactoryDrawable::getInstance()->createMovingStarsBackground()),
  _scrollingBackground2(*scrollingBackground2)
{

  scrollingBackground->update(10000);

}


SceneBackground::~SceneBackground(void)
{
}

IScene* SceneBackground::update(float elapsedTime)
{
  _fixedBackground.update(elapsedTime);
  fixedBackground->update(elapsedTime);
  _scrollingBackground.update(elapsedTime);
  scrollingBackground->update(elapsedTime);
  _scrollingBackground2.update(elapsedTime);
  scrollingBackground2->update(elapsedTime);
  return this;
}

void SceneBackground::draw()
{
  IGraphicsManager* gm = SceneManager::getInstance()->getGraphicsManager();

  _fixedBackground.drawTo(gm);
  _scrollingBackground.drawTo(gm);
  _scrollingBackground2.drawTo(gm);
}

void SceneBackground::load()
{

}

void SceneBackground::unload()
{

}

void SceneBackground::setToBackground()
{

}

void SceneBackground::setToForeground()
{

}
