#include "ASceneHover.h"


ASceneHover::ASceneHover(IScene& _decoratedScene) : decoratedScene(_decoratedScene)
{
}


ASceneHover::~ASceneHover(void)
{
}

IScene* ASceneHover::getParentScene() {
	return &decoratedScene;
}

IScene* ASceneHover::update(float time)
{
	return decoratedScene.update(time);
}

void ASceneHover::draw()
{
	decoratedScene.draw();
}