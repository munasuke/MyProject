#include "Stage.h"



Stage::Stage()
{
	memset(&_stageRange, 0, sizeof(_stageRange));
}


Stage::~Stage() {
}

//�X�e�[�W�͈̔͂�Ԃ�
const Rect & Stage::GetStageRange() const {
	return _stageRange;
}
