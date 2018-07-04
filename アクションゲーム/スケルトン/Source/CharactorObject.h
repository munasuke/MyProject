#pragma once
#include "Typedef.h"
#include <string>
#include <map>
#include <vector>
#include <memory>

class Camera;

//�L�����N�^�[�R���g���[��
class CharactorObject
{
public:
	CharactorObject();
	~CharactorObject();
	virtual void Updata() = 0;
	virtual void Draw() = 0;
protected:
	void ChangeMode(std::string md);//��Ԑ؂�ւ�
	void Load(std::string filepath);//�t�@�C���ǂݍ���
	void DrawRect(positin _pos);//�U����`�A�����`�̕`��
	bool IsCollision(AttackRect& rec1, AttackRect& rec2, positin pos1, positin pos2);

	int _currentCutIndex;//���ݕ\�����̃J�b�g�C���f�b�N�X
	unsigned int _flame;//�o�߃t���[��
	positin pos;
	positin velocity;
	const float gravity;
	bool _jump;//�W�����v�t���O
	bool turnFlag;//�摜�̔��]�t���O
	int image;//�摜�n���h��
	int _damageSE;//�_���[�WSE
	unsigned int life;
	int speed;

	//���
	std::string mode;
	// �w�b�_�[
	Header header;
	//�A�N�V�����f�[�^
	std::map<int, ImageDate> data;
	//�����f�[�^
	std::map<std::string, std::vector<CutDate>> cut;
	//�U����`
	std::map < std::string, std::map<int, std::vector<AttackRect>>> attackRect;

	std::weak_ptr<Camera> camera;
};

