#pragma once
#include "Typedef.h"
#include <memory>
#include <map>
#include <string>

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
	void SetAnimation(int _index);

	void NeutralUpdata();
	void WalkUpdata();
	void(Player::*updata)();//ステータスのメンバ関数ポインタ

	std::weak_ptr<KeyInput> key;

	//ハンドル
	int playerH;

	//アニメーション
	int animIndex;//番号
	float animTime;//カウント用
	float animTimeTotal;//総再生時間
	std::map<std::string, int> anim;//状態に合ったアニメーションを取得

	bool onceflag;

	//ステータス
	positin3D pos;//座標
	positin3D rot;//角度
	float speed;//移動速度
};

