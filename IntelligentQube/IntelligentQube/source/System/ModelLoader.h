#pragma once
#include <map>
#include <string>
#include <Windows.h>

class ModelLoader {
public:
	ModelLoader();
	~ModelLoader();
	
	int PreLoad(TCHAR* filepath);//先読み関数
	int Load(TCHAR* filepath);//読み込み関数
private:
	struct ModelInfo {
		int handle;//ハンドル
		bool useFlag;//true : 読み込んでいる, false : 読み込んでいない
	};
	//パスを受け取る変数
	std::map<TCHAR*, ModelInfo> modelInfo;
};

