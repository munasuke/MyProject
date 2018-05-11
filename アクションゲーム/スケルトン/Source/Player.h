#pragma once
#include "Typedef.h"
#include <vector>
#include <map>
#include <string>

#define key(X) (key[X]&old_key[X])^key[X]//トリガー処理

class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw();
	positin GetPos();
	positin GetVec();
private:
	void Load();
	void Jump();
	void Crouch();
	void Punch();
	void Kick();
	void NeutralUpdate();
	void WalkUpdate();
	void JumpUpdate();
	void CrouchUpdate();
	void PunchUpdate();
	void KickUpdate();
	void DamageUpdate();
	void ChangeMode(std::string md);//状態切り替え

	int player;
	positin pos;
	positin velocity;
	const float gravity;
	bool _jump;//ジャンプフラグ

	char key[256];
	char old_key[256];

	void (Player::*_update)();

	bool turnFlag;//画像の反転フラグ
	int _currentCutIndex;//現在表示中のカットインデックス
	unsigned int _flame;//経過フレーム

	//状態
	std::string mode;

	// ヘッダー
	Header header;
	//アクションデータ
	std::map<int, ImageDate> date;
	//分割データ
	std::map<std::string, std::vector<CutDate>> cut;
	//攻撃矩形
	std::map < std::string, std::vector<AttackRect>> attackRect;
};

