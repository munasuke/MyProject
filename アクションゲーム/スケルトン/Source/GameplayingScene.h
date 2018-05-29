#pragma once
#include "Scene.h"
#include "Game.h"
#include "CountinueScene.h"
#include "DxLib.h"

class GameplayingScene :
	public Scene
{
public:
	GameplayingScene();
	~GameplayingScene();
	void Updata();
};

