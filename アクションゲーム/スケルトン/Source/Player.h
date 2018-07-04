#pragma once
#include "Typedef.h"
#include "KeyInput.h"
#include "CharactorObject.h"
#include <vector>
#include <map>
#include <string>
#include <memory>
class Camera;

//プレイヤー管理クラス
class Player : public CharactorObject
{
public:
	Player(std::weak_ptr<KeyInput> _key, std::weak_ptr<Camera> _camera);
	~Player();
	void Updata();
	void Draw();
	positin GetPos();
	positin GetLocalPos();
	positin GetVec();
	std::vector<AttackRect> GetActRect();
	void Damage();
	std::string GetActMode();
	int GetLife();
private:
	//状態
	void Jump();
	void Crouch();
	void Punch();
	void Kick();
	void Sliding();
	//状態更新
	void NeutralUpdata();
	void WalkUpdata();
	void JumpUpdata();
	void CrouchUpdata();
	void PunchUpdata();
	void KickUpdata();
	void SlidingUpdata();
	void DamageUpdata();

	void (Player::*_updata)();
	int _damageTime;//ダメージ時の待機時間
	bool _walk;//直前に歩いていたか管理
	int ground;//地面
	std::weak_ptr<KeyInput> key;
	int _life;//ライフ
	positin localPos;//ローカル座標
};

