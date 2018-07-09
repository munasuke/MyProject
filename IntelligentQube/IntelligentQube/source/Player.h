#pragma once
#include "Typedef.h"
#include "DxLib.h"
#include <memory>

#define RAD(X) X * DX_PI_F / 180.0f

class KeyInput;

class Player {
public:
	Player(std::weak_ptr<KeyInput> _key);
	~Player();

	void Updata();
	void Draw();

	int GetPlayerHandle();
private:
	void Move();
	void Animation();

	std::weak_ptr<KeyInput> key;

	int playerH;//���f���n���h��

	int animIndex;//�A�j���[�V�����ԍ�
	float animTime;//�J�E���g�p
	float animTimeTotal;//�A�j���[�V�����̑��Đ�����

	bool onceflag;

	positin3D pos;//���W
	positin3D rot;//�p�x

	float speed;//�ړ����x
};

