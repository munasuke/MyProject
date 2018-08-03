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
	void SetPlayerHandle(int handle);
	positin3D GetPosition();
private:
	//キー情報
	std::weak_ptr<KeyInput> key;

	//ハンドル
	int playerH;

	void Move();

	//アニメーション
	void Animation();
	void SetAnimation(std::string state);
	int animIndex;//番号
	float animTime;//カウント用
	float animTimeTotal;//総再生時間
	std::map<std::string, int> anim;//状態に合ったアニメーションを取得

	//状態遷移
	void NeutralUpdata();
	void WalkUpdata();
	void(Player::*updata)();//ステータスのメンバ関数ポインタ

	//ステータス
	positin3D pos;//座標
	positin3D rot;//角度
	float speed;//移動速度
};

