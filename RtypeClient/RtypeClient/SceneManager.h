#pragma once
class SceneManager
{
public:
	~SceneManager(void);
	static SceneManager* getInstance();

	//getInputManager();
	void draw();
	void update();
	void changeScene();
private:
	static SceneManager* instance;

	SceneManager(void);
};

