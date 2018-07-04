#pragma once
#include "Typedef.h"
#include <vector>

#define CHIP_SIZE 64

class Stage {
public:
	Stage();
	~Stage();

	void Update();

	void Load(std::string fileName);

	const Rect& GetStageRange() const;

	std::vector<UCHAR>GetEnemyData(int minx, int max);
	std::vector<UCHAR>GetEventData(int minx, int max);

private:
	Rect _stageRange;

	StageHeader stData;

	std::vector<UCHAR> enemyData;
	std::vector<UCHAR> eventData;

	int readX, readY;
};

