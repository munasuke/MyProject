#pragma once
#include "Dxlib.h"
#include <vector>

#define CNT_MAX 60
const int maxWaitTime = 180;

enum Direction{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

//キューブ管理
class Cube {
public:
	Cube();
	Cube(VECTOR _pos, VECTOR _scale = { 1.0f, 1.0f, 1.0f }, COLOR_F _color = { 0.2f, 0.2f, 0.2f, 1.0f });
	virtual ~Cube();

	void Updata();
	void Draw();

	void RollOver(float x, float z);

	float GetPosition();
protected:
	void SetUpPolygon();

	//状態
	void WaitUpdata();//待機中
	void RollingUpdata();//回転中
	void RolledUpdata();//回転後、重心再計算
	void FallingUpdata();//落下中
	void(Cube::*updata)();//状態遷移用メンバ関数ポインタ

	VECTOR SetCentorPos(std::vector<VERTEX3D> ver);//中心点を求める

	int cubeH;
	VECTOR angle;
	VECTOR pos;
	VECTOR centorPos;//中心座標
	VECTOR velocity;

	std::vector<VERTEX3D> vertex;
	std::vector<unsigned short> indices;
	std::vector<VERTEX3D> verts;
	MATRIX rollingMat;
	MATRIX mixMat;

	int moveCnt;
	int waitTime;//待機時間
	bool waitFlag;//待機フラグ(true:待機, false:行動)
	MATERIALPARAM mt;
	int impactH;

	//Debug用
	bool flg;
	bool flg2;
};

