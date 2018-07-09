#pragma once
#include "Typedef.h"
#include <vector>
#include <map>


class Load
{
public:
	~Load();

	// �C���X�^���X��
	static void Create(void);
	// �j��
	static void Destroy(void);

	// �C���X�^���X�ϐ��̎擾
	static Load* GetInstance(void)
	{
		return s_Instance;
	}

	bool LoadMap(std::string fileName);


	// �X�e�[�W�w�b�_�[�̎擾
	StageHeader GetStageHeader(std::string fileName);

	// �X�e�[�W�̓G�f�[�^�̎擾
	std::vector<unsigned char>GetEnemyData(std::string fileName);

	// �X�e�[�W�̃C�x���g�f�[�^�̎擾
	std::vector<unsigned char>GetEventData(std::string fileName);

	int LoadImg(std::string name);

private:
	// �R���X�g���N�^
	Load();

	// �C���X�^���X�ϐ�
	static Load* s_Instance;

	// �X�e�[�W�w�b�_�[
	std::map<std::string, StageHeader>st;

	// �X�e�[�W�̓G�f�[�^
	std::map<std::string, std::vector<unsigned char>>enemyData;

	// �X�e�[�W�̃C�x���g�f�[�^
	std::map<std::string, std::vector<unsigned char>>eventData;

	std::map<std::string, int> image;
};