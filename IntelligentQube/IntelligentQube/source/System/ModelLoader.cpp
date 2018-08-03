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
	//�R���e�i�ɂ��邩�`�F�b�N
	if (modelInfo.find(filepath) == modelInfo.end()) {
		//�Ȃ��̂Ń��[�h
		modelInfo[filepath].handle = MV1LoadModel(filepath);
		return modelInfo[filepath].handle;
	}
	else {
		//����̂�
		return MV1DuplicateModel(modelInfo[filepath].handle);
	}
}
