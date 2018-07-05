#pragma once
#include "Scene/Scene.h"
#include "DxLib.h"
#include <memory>

#define RAD(X) X * DX_PI_F / 180.0f

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
	int _playerH;
	VECTOR _pos;
	VECTOR _rot;
};

