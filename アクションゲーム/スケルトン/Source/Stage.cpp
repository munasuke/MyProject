#include "Stage.h"
#include "Load.h"
#include <algorithm>


Stage::Stage()
{
	const char* path = "Stage/stage1.fmf";
	readX = 2;
	readY = 2;
	Load(path);
}


Stage::~Stage() {
}

void Stage::Update()
{
}

void Stage::Load(std::string fileName)
{
	Load::GetInstance()->LoadMap(fileName);

	stData = Load::GetInstance()->GetStageHeader(fileName);
	stData.chipHeight *= 2;
	stData.chipWidth *= 2;

	_stageRange = Rect(0, 0, (stData.mapWidth * CHIP_SIZE) * 2, (stData.mapHeight * CHIP_SIZE));
	enemyData = Load::GetInstance()->GetEnemyData(fileName);
	eventData = Load::GetInstance()->GetEventData(fileName);
}

const Rect & Stage::GetStageRange() const {
	return _stageRange;
}

std::vector<unsigned char> Stage::GetEnemyData(int minx, int _max) {
	int left = std::max(minx / CHIP_SIZE, readX);
	int right = _max / CHIP_SIZE;
	if (right <= readX) {
		return std::vector<unsigned char>();
	}

	auto index = left * stData.mapHeight;
	auto index2 = right * stData.mapHeight;

	auto begin = enemyData.begin() + index;
	auto itr = enemyData.end();
	auto end = itr;

	if (index2 < enemyData.size()) {
		end = enemyData.begin() + index2;
		readX = right;
	}
	else {
		return std::vector<unsigned char>();
	}
	return std::vector<unsigned char>(begin, end);
}

std::vector<unsigned char> Stage::GetEventData(int minx, int _max) {
	int left = std::max(minx / CHIP_SIZE, readY);
	int right = _max / CHIP_SIZE;
	if (right <= readY) {
		return std::vector<unsigned char>();
	}

	auto index = left * stData.mapHeight;
	auto index2 = right * stData.mapHeight;

	auto begin = eventData.begin() + index;
	auto itr = eventData.end();
	auto end = itr;

	if (index2 < eventData.size()) {
		end = eventData.begin() + index2;
		readY = right;
	}
	else {
		return std::vector<unsigned char>();
	}
	return std::vector<unsigned char>(begin, end);
}
