#pragma once
#include "Typedef.h"
#include <string>
#include <map>
#include <vector>

//キャラクターコントロール
class CharactorObject
{
public:
	CharactorObject();
	~CharactorObject();
protected:
	void ChangeMode(std::string md);//状態切り替え
	void Load(std::string filepath);//ファイル読み込み

	int _currentCutIndex;//現在表示中のカットインデックス
	unsigned int _flame;//経過フレーム
	positin pos;
	positin velocity;
	const float gravity;
	bool _jump;//ジャンプフラグ
	bool turnFlag;//画像の反転フラグ
	int image;//画像ハンドル

	//状態
	std::string mode;
	// ヘッダー
	Header header;
	//アクションデータ
	std::map<int, ImageDate> data;
	//分割データ
	std::map<std::string, std::vector<CutDate>> cut;
	//攻撃矩形
	std::map < std::string, std::vector<AttackRect>> attackRect;
};

