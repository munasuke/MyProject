#include "Stage.h"



Stage::Stage()
{
	memset(&_stageRange, 0, sizeof(_stageRange));
	_stageRange = { 0,0,4000, 480 };
}


Stage::~Stage() {
}

//�X�e�[�W�͈̔͂�Ԃ�
const Rect & Stage::GetStageRange() const {
	return _stageRange;
}
