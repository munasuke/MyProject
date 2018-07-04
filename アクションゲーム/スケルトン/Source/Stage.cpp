#include "Stage.h"



Stage::Stage()
{
	memset(&_stageRange, 0, sizeof(_stageRange));
	_stageRange = { 0,0,4000, 480 };
}


Stage::~Stage() {
}

//ステージの範囲を返す
const Rect & Stage::GetStageRange() const {
	return _stageRange;
}
