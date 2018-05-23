#pragma once
#include "Typedef.h"
#include "CharactorObject.h"
#include <vector>
#include <map>
#include <string>

#define key(X) (key[X]&old_key[X])^key[X]//トリガー処理

//プレイヤー管理クラス
class Player : public CharactorObject
{
public:
	Player();
	~Player();
	void Updata();
	void Draw();
	positin GetPos();
	positin GetVec();
	std::vector<AttackRect> GetActRect();
	void Damage();
	std::string GetActMode();
private:

	//状態
	void Jump();
	void Crouch();
	void Punch();
	void Kick();
	void Sliding();
	void NeutralUpdata();
	void WalkUpdata();
	void JumpUpdata();
	void CrouchUpdata();
	void PunchUpdata();
	void KickUpdata();
	void SlidingUpdata();
	void DamageUpdata();


	char key[256];
	char old_key[256];

	void (Player::*_updata)();
	int _damageTime;//ダメージ時の待機時間
	bool _walk;//直前に歩いていたか管理
	int ground;
};

