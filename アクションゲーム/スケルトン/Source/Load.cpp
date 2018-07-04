#include "Load.h"
#include <cassert>
#include <tchar.h>

Load* Load::s_Instance = nullptr;

// コンストラクタ
Load::Load()
{
	st.clear();
	enemyData.clear();
	eventData.clear();
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



// 破棄

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

	for (auto itr = st.begin(); itr != st.end(); ++itr)
	{
		if (fileName == itr->first)
		{
			return true;
			break;
		}
	}

	//ファイル開らく
	if ((fopen_s(&file, fileName.c_str(), "rb")) != 0)
	{
		return false;
	}

	fread(&st[fileName], sizeof(st[fileName]), 1, file);

	std::vector<UCHAR>dummy;

	dummy.resize(st[fileName].mapHeight * st[fileName].mapWidth);

	enemyData[fileName].resize(st[fileName].mapHeight * st[fileName].mapWidth);

	for (UINT i = 0; i < enemyData[fileName].size(); ++i)
	{
		fread(&dummy[i], sizeof(UCHAR), 1, file);
	}

	std::vector<UCHAR>edummy;

	edummy.resize(st[fileName].mapHeight * st[fileName].mapWidth);

	eventData[fileName].resize(st[fileName].mapHeight * st[fileName].mapWidth);

	for (UINT i = 0; i < eventData[fileName].size(); ++i)
	{
		fread(&edummy[i], sizeof(UCHAR), 1, file);
	}

	fclose(file);

	for (UINT i = 0; i < st[fileName].mapHeight; ++i)
	{
		for (UINT j = 0; j < st[fileName].mapWidth; ++j)
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
std::vector<UCHAR> Load::GetEnemyData(std::string fileName)
{
	return enemyData[fileName];
}

// ステージのイベントデータの取得
std::vector<UCHAR> Load::GetEventData(std::string fileName)
{
	return eventData[fileName];
}