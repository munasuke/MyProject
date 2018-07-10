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
	void(Player::*updata)();//�X�e�[�^�X�̃����o�֐��|�C���^

	std::weak_ptr<KeyInput> key;

	//�n���h��
	int playerH;

	//�A�j���[�V����
	int animIndex;//�ԍ�
	float animTime;//�J�E���g�p
	float animTimeTotal;//���Đ�����
	std::map<std::string, int> anim;//��Ԃɍ������A�j���[�V�������擾

	bool onceflag;

	//�X�e�[�^�X
	positin3D pos;//���W
	positin3D rot;//�p�x
	float speed;//�ړ����x
};

