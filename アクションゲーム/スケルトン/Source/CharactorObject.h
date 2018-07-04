#pragma once
#include "Typedef.h"
#include <string>
#include <map>
#include <vector>
#include <memory>

class Camera;

//キャラクターコントロール
class CharactorObject
{
public:
	CharactorObject();
	~CharactorObject();
	virtual void Updata() = 0;
	virtual void Draw() = 0;
protected:
	void ChangeMode(std::string md);//状態切り替え
	void Load(std::string filepath);//ファイル読み込み
	void DrawRect(positin _pos);//攻撃矩形、やられ矩形の描画
	bool IsCollision(AttackRect& rec1, AttackRect& rec2, positin pos1, positin pos2);

	int _currentCutIndex;//現在表示中のカットインデックス
	unsigned int _flame;//経過フレーム
	positin pos;
	positin velocity;
	const float gravity;
	bool _jump;//ジャンプフラグ
	bool turnFlag;//画像の反転フラグ
	int image;//画像ハンドル
	int _damageSE;//ダメージSE
	unsigned int life;
	int speed;

	//状態
	std::string mode;
	// ヘッダー
	Header header;
	//アクションデータ
	std::map<int, ImageDate> data;
	//分割データ
	std::map<std::string, std::vector<CutDate>> cut;
	//攻撃矩形
	std::map < std::string, std::map<int, std::vector<AttackRect>>> attackRect;

	std::weak_ptr<Camera> camera;
};

