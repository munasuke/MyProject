#pragma once
#include "Scene/Scene.h"
#include "Typedef.h"
#include "DxLib.h"
#include <memory>
#include <vector>

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
	void CameraRotation(float x, float y, const float ang, const float mx, const float my);
	positin3D camPos;
	positin3D targetPos;
	VECTOR toEyeVector;//逆視線ベクトル

	std::shared_ptr<NowLoading> ld;//ローディング
	std::shared_ptr<Player> pl;//プレイヤー
	std::shared_ptr<Cube> cube;//キューブ
	std::vector<std::shared_ptr<Cube>> cb;
	std::shared_ptr<Cube> groundCube;//床
};

