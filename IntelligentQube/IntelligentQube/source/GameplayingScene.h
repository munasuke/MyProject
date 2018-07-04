#pragma once
#include "Scene/Scene.h"
#include <memory>


class GameplayingScene :
	public Scene
{
public:
	GameplayingScene(std::weak_ptr<KeyInput> _key);
	~GameplayingScene();
	void Updata();
	void Draw();
	void FadeIn();
	void FadeOut();
private:
};

