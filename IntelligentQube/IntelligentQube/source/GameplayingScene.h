#pragma once
#include "Scene/Scene.h"
#include "DxLib.h"
#include <memory>

class NowLoading;
class Player;
class Cube;

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
	std::shared_ptr<NowLoading> ld;
	std::shared_ptr<Player> pl;
	std::shared_ptr<Cube> cube;
};

