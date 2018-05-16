#pragma once
#include "Typedef.h"
#include "CharactorObject.h"
#include <vector>
#include <map>
#include <string>

#define key(X) (key[X]&old_key[X])^key[X]//�g���K�[����

//�v���C���[�Ǘ��N���X
class Player : CharactorObject
{
public:
	Player();
	~Player();
	void Updata();
	void Draw();
	positin GetPos();
	positin GetVec();
private:

	//���
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


};

