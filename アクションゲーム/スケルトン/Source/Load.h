#pragma once
#include "Typedef.h"
#include <vector>
#include <map>


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
	std::vector<unsigned char>GetEnemyData(std::string fileName);

	// ステージのイベントデータの取得
	std::vector<unsigned char>GetEventData(std::string fileName);

	int LoadImg(std::string name);

private:
	// コンストラクタ
	Load();

	// インスタンス変数
	static Load* s_Instance;

	// ステージヘッダー
	std::map<std::string, StageHeader>st;

	// ステージの敵データ
	std::map<std::string, std::vector<unsigned char>>enemyData;

	// ステージのイベントデータ
	std::map<std::string, std::vector<unsigned char>>eventData;

	std::map<std::string, int> image;
};