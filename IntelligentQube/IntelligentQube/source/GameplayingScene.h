#pragma once
#include "Scene/Scene.h"
#include "DxLib.h"
#include <memory>

const float Angle = DX_PI_F / 90.0f;

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
	void CameraRotation(float *x, float *y, const float ang, const float mx, const float my);
	VECTOR camPos;
	VECTOR targetPos;

	std::shared_ptr<NowLoading> ld;
	std::shared_ptr<Player> pl;
	std::shared_ptr<Cube> cube;
};

