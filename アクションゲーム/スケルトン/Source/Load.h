#pragma once

#include "typedef.h"
#include <vector>
#include <map>
#include <string>
#include <Windows.h>


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
	std::vector<UCHAR>GetEnemyData(std::string fileName);

	// �X�e�[�W�̃C�x���g�f�[�^�̎擾
	std::vector<UCHAR>GetEventData(std::string fileName);

private:
	// �R���X�g���N�^
	Load();

	// �C���X�^���X�ϐ�
	static Load* s_Instance;

	// �X�e�[�W�w�b�_�[
	std::map<std::string, StageHeader>st;

	// �X�e�[�W�̓G�f�[�^
	std::map<std::string, std::vector<UCHAR>>enemyData;

	// �X�e�[�W�̃C�x���g�f�[�^
	std::map<std::string, std::vector<UCHAR>>eventData;
};