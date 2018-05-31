#pragma once
#include "Scene.h"

class GameoverScene :
	public Scene
{
public:
	GameoverScene(std::weak_ptr<KeyInput> _key);
	~GameoverScene();
	void Updata();
	void Draw();
	void FadeIn();
	void FadeOut();
private:
	int overImage;
};

