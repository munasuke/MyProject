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
	//�L�[���
	std::weak_ptr<KeyInput> key;

	//�n���h��
	int playerH;

	void Move();

	//�A�j���[�V����
	void Animation();
	void SetAnimation(std::string state);
	int animIndex;//�ԍ�
	float animTime;//�J�E���g�p
	float animTimeTotal;//���Đ�����
	std::map<std::string, int> anim;//��Ԃɍ������A�j���[�V�������擾

	//��ԑJ��
	void NeutralUpdata();
	void WalkUpdata();
	void(Player::*updata)();//�X�e�[�^�X�̃����o�֐��|�C���^

	//�X�e�[�^�X
	positin3D pos;//���W
	positin3D rot;//�p�x
	float speed;//�ړ����x
};

