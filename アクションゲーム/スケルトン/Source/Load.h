#pragma once

#include "typedef.h"
#include <vector>
#include <map>
#include <string>
#include <Windows.h>


class Load
{
public:
	~Load();

	// インスタンス化
	static void Create(void);
	// 破棄
	static void Destroy(void);

	// インスタンス変数の取得
	static Load* GetInstance(void)
	{
		return s_Instance;
	}

	bool LoadMap(std::string fileName);


	// ステージヘッダーの取得
	StageHeader GetStageHeader(std::string fileName);

	// ステージの敵データの取得
	std::vector<UCHAR>GetEnemyData(std::string fileName);

	// ステージのイベントデータの取得
	std::vector<UCHAR>GetEventData(std::string fileName);

private:
	// コンストラクタ
	Load();

	// インスタンス変数
	static Load* s_Instance;

	// ステージヘッダー
	std::map<std::string, StageHeader>st;

	// ステージの敵データ
	std::map<std::string, std::vector<UCHAR>>enemyData;

	// ステージのイベントデータ
	std::map<std::string, std::vector<UCHAR>>eventData;
};