#pragma once
#include "Typedef.h"
#include <vector>
#include <map>
#include <string>

#define key(X) (key[X]&old_key[X])^key[X]//�g���K�[����

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
	void ChangeMode(std::string md);//��Ԑ؂�ւ�

	int player;
	positin pos;
	positin velocity;
	const float gravity;
	bool _jump;//�W�����v�t���O

	char key[256];
	char old_key[256];

	void (Player::*_update)();

	bool turnFlag;//�摜�̔��]�t���O
	int _currentCutIndex;//���ݕ\�����̃J�b�g�C���f�b�N�X
	unsigned int _flame;//�o�߃t���[��

	//���
	std::string mode;

	// �w�b�_�[
	Header header;
	//�A�N�V�����f�[�^
	std::map<int, ImageDate> date;
	//�����f�[�^
	std::map<std::string, std::vector<CutDate>> cut;
	//�U����`
	std::map < std::string, std::vector<AttackRect>> attackRect;
};

