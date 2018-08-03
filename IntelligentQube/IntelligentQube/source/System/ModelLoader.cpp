#include "ModelLoader.h"
#include "DxLib.h"


ModelLoader::ModelLoader() {
	SetUseASyncLoadFlag(true);
}


ModelLoader::~ModelLoader() {
}

int ModelLoader::PreLoad(TCHAR * filepath)
{
	modelInfo[filepath].handle = MV1LoadModel(filepath);
	return modelInfo[filepath].handle;
}

int ModelLoader::Load(TCHAR* filepath) {
	//コンテナにあるかチェック
	if (modelInfo.find(filepath) == modelInfo.end()) {
		//ないのでロード
		modelInfo[filepath].handle = MV1LoadModel(filepath);
		return modelInfo[filepath].handle;
	}
	else {
		//あるので
		return MV1DuplicateModel(modelInfo[filepath].handle);
	}
}
