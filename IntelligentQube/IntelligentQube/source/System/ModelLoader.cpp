#include "ModelLoader.h"
#include "DxLib.h"


ModelLoader::ModelLoader() {
	SetUseASyncLoadFlag(true);
}


ModelLoader::~ModelLoader() {
}

int ModelLoader::Load(std::string filepath) {
	//filepathがmap内にあるか見る
	//あればデュプリケート、なければロード
	return 0;
}
