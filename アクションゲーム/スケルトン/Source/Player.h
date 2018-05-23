#pragma once
#include "Typedef.h"
#include "CharactorObject.h"
#include <vector>
#include <map>
#include <string>

#define key(X) (key[X]&old_key[X])^key[X]//�g���K�[����

//�v���C���[�Ǘ��N���X
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
	int _damageTime;//�_���[�W���̑ҋ@����
	bool _walk;//���O�ɕ����Ă������Ǘ�
	int ground;
};

