#pragma once
#include <map>
#include <string>
#include <Windows.h>

class ModelLoader {
public:
	ModelLoader();
	~ModelLoader();
	
	int PreLoad(TCHAR* filepath);//��ǂ݊֐�
	int Load(TCHAR* filepath);//�ǂݍ��݊֐�
private:
	struct ModelInfo {
		int handle;//�n���h��
		bool useFlag;//true : �ǂݍ���ł���, false : �ǂݍ���ł��Ȃ�
	};
	//�p�X���󂯎��ϐ�
	std::map<TCHAR*, ModelInfo> modelInfo;
};

