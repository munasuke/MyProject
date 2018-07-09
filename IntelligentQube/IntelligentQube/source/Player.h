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

	int playerH;//モデルハンドル

	int animIndex;//アニメーション番号
	float animTime;//カウント用
	float animTimeTotal;//アニメーションの総再生時間

	bool onceflag;

	positin3D pos;//座標
	positin3D rot;//角度

	float speed;//移動速度
};

