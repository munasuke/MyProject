#pragma once
#include <map>
#include <string>

class ModelLoader {
public:
	ModelLoader();
	~ModelLoader();

	int Load(std::string filepath);
private:
	struct ModelInfo {
		int handle;//�n���h��
		bool useFlag;//true : �ǂݍ���ł���, false : �ǂݍ���ł��Ȃ�
	};
	//�p�X���󂯎��ϐ�
	std::map<std::string, ModelInfo> modelInfo;
};

