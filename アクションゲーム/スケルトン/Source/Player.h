#pragma once
#include "Typedef.h"
#include "KeyInput.h"
#include "CharactorObject.h"
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <string>
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
	void SetActMode(std::string name);
	int GetLife();
	bool GetDieFlag();
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
	void DieUpdata();
	void LadderUpdata();

	void (Player::*_updata)();
	int _damageTime;//ダメージ時の待機時間
	bool _walk;//直前に歩いていたか管理
	int ground;//地面
	std::weak_ptr<KeyInput> key;
	int _life;//ライフ
	int _ultimateTime;//無敵時間
	positin localPos;//ローカル座標
	int _alpha;//アルファ値
	bool _aFlag;
	int _deathTime;
	std::map<std::string, int> se;//各種SE

	bool dieFlag;

	std::string old_mode;
};

