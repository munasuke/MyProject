#include "Load.h"
#include "DxLib.h"
#include <cassert>
#include <tchar.h>

Load* Load::s_Instance = nullptr;

Load::Load()
{
	st.clear();
	enemyData.clear();
	eventData.clear();
	image.clear();
}

// デストラクタ
Load::~Load()
{
}

// インスタンス化
void Load::Create(void)
{

	if (s_Instance == nullptr)
	{
		s_Instance = new Load;
	}
}

void Load::Destroy(void)
{
	if (s_Instance != nullptr)
	{
		delete s_Instance;
	}
	s_Instance = nullptr;
}

// 読み込み
bool Load::LoadMap(std::string fileName)
{
	FILE* file;

	int n = st.size();

	for (auto itr = st.begin(); itr != st.end(); ++itr)
	{
		if (fileName == itr->first)
		{
			return true;
			break;
		}
	}

	if ((fopen_s(&file, fileName.c_str(), "rb")) != 0)
	{
		return false;
	}

	fread(&st[fileName], sizeof(st[fileName]), 1, file);

	std::vector<unsigned char>dummy;

	dummy.resize(st[fileName].mapHeight * st[fileName].mapWidth);

	enemyData[fileName].resize(st[fileName].mapHeight * st[fileName].mapWidth);

	for (unsigned int i = 0; i < enemyData[fileName].size(); ++i)
	{
		fread(&dummy[i], sizeof(unsigned char), 1, file);
	}

	std::vector<unsigned char>edummy;

	edummy.resize(st[fileName].mapHeight * st[fileName].mapWidth);

	eventData[fileName].resize(st[fileName].mapHeight * st[fileName].mapWidth);

	for (unsigned int i = 0; i < eventData[fileName].size(); ++i)
	{
		fread(&edummy[i], sizeof(unsigned char), 1, file);
	}

	fclose(file);

	for (unsigned int i = 0; i < st[fileName].mapHeight; ++i)
	{
		for (unsigned int j = 0; j < st[fileName].mapWidth; ++j)
		{
			enemyData[fileName][j * st[fileName].mapHeight + i] = dummy[i * st[fileName].mapWidth + j];
			eventData[fileName][j * st[fileName].mapHeight + i] = edummy[i * st[fileName].mapWidth + j];
		}
	}
	return true;
}

// ステージヘッダーの取得
StageHeader Load::GetStageHeader(std::string fileName)
{
	return st[fileName];
}

// ステージの敵データの取得
std::vector<unsigned char> Load::GetEnemyData(std::string fileName)
{
	return enemyData[fileName];
}

// ステージのイベントデータの取得
std::vector<unsigned char> Load::GetEventData(std::string fileName)
{
	return eventData[fileName];
}

int Load::LoadImg(std::string name) {

	if (image.find(name) != image.end()){
		return image[name];
	}
	else{
		return image[name] = LoadGraph(name.c_str());
	}

	return -1;
}
