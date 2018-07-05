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

	std::vector<unsigned char>GetEnemyData(int minx, int max);
	std::vector<unsigned char>GetEventData(int minx, int max);

private:
	Rect _stageRange;

	StageHeader stData;

	std::vector<unsigned char> enemyData;
	std::vector<unsigned char> eventData;

	int readX, readY;
};

