#include "Stage.h"
#include "Load.h"


Stage::Stage()
{
	const char* path = "stage/stage1.fmf";
	Load(path);
	readX = 2;
	readY = 2;
	//memset(&_stageRange, 0, sizeof(_stageRange));
	//_stageRange = { 0,0,4000, 480 };
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

//ステージの範囲を返す
const Rect & Stage::GetStageRange() const {
	return _stageRange;
}

std::vector<UCHAR> Stage::GetEnemyData(int minx, int max)
{
	int left = max(minx / CHIP_SIZE, readX);
	int right = max / CHIP_SIZE;
	if (right <= readX) {
		return std::vector<UCHAR>();
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
		return std::vector<UCHAR>();
	}

	return std::vector<UCHAR>(begin, end);
}

std::vector<UCHAR> Stage::GetEventData(int minx, int max)
{
	int left = max(minx / CHIP_SIZE, readY);
	int right = max / CHIP_SIZE;
	if (right <= readY) {
		return std::vector<UCHAR>();
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
		return std::vector<UCHAR>();
	}

	return std::vector<UCHAR>(begin, end);
}
