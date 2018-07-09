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

//�v���C���[�Ǘ��N���X
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
	//���
	void Jump();
	void Crouch();
	void Punch();
	void Kick();
	void Sliding();
	//��ԍX�V
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
	int _damageTime;//�_���[�W���̑ҋ@����
	bool _walk;//���O�ɕ����Ă������Ǘ�
	int ground;//�n��
	std::weak_ptr<KeyInput> key;
	int _life;//���C�t
	int _ultimateTime;//���G����
	positin localPos;//���[�J�����W
	int _alpha;//�A���t�@�l
	bool _aFlag;
	int _deathTime;
	std::map<std::string, int> se;//�e��SE

	bool dieFlag;

	std::string old_mode;
};

