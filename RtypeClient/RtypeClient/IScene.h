#pragma once
class IScene
{
public:
	virtual IScene* update(float elapsedTime) = 0;
	virtual void load() = 0;
	virtual void unload() = 0;
	virtual void setToBackground() = 0;
	virtual void setToForeground() = 0;
};
