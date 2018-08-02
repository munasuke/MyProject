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
	void CameraRotation(VECTOR vec1, VECTOR vec2);
	positin3D camPos;
	positin3D targetPos;
	VECTOR toEyeVector;//�t�����x�N�g��

	std::shared_ptr<NowLoading> ld;//���[�f�B���O
	std::shared_ptr<Player> pl;//�v���C���[
	std::shared_ptr<Cube> cube;//�L���[�u
	std::vector<std::shared_ptr<Cube>> cb;
	std::shared_ptr<Cube> groundCube;//��
};

