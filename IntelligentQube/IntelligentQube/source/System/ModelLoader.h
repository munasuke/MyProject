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
		int handle;//ハンドル
		bool useFlag;//true : 読み込んでいる, false : 読み込んでいない
	};
	//パスを受け取る変数
	std::map<std::string, ModelInfo> modelInfo;
};

