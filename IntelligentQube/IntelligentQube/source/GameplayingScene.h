#pragma once
#include "Scene/Scene.h"
#include "Typedef.h"
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
	positin3D PlusVECTOR(positin3D pos, VECTOR vec);
	void CameraRotation(float *x, float *y, const float ang, const float mx, const float my);
	positin3D camPos;
	positin3D targetPos;
	VECTOR toEyeVector;//ãtéãê¸ÉxÉNÉgÉã

	std::shared_ptr<NowLoading> ld;
	std::shared_ptr<Player> pl;
	std::shared_ptr<Cube> cube;
};

