#pragma once
#include "IScene.h"
#include "IDrawable.h"

class ASceneHover :
	public IScene
{
public:
	ASceneHover(IScene& _decoratedScene);
	~ASceneHover(void);
	IScene* getParentScene();
	virtual IScene* update(float time);
	virtual void draw();
protected:
	IScene& decoratedScene;
};

