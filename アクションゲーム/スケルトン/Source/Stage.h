#pragma once
#include "Typedef.h"

class Stage {
public:
	Stage();
	~Stage();
	const Rect& GetStageRange() const;

private:
	Rect _stageRange;
};

