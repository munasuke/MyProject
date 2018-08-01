#pragma once
#include "Dxlib.h"
#include <vector>

#define CNT_MAX 60

enum Direction{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

//キューブ管理
class Cube {
public:
	Cube(VECTOR _pos, VECTOR _scale = {1.0f, 1.0f, 1.0f});
	virtual ~Cube();

	void Updata();
	void Draw();

	void RollOver(float x, float z);
protected:
	void SetUpPolygon();

	//状態
	void WaitUpdata();//待機中
	void RollingUpdata();//回転中
	void RolledUpdata();//回転後、重心再計算
	void(Cube::*updata)();//状態遷移用メンバ関数ポインタ

	VECTOR SetCentorPos(std::vector<VERTEX3D> ver);//中心点を求める

	int cubeH;
	float angle;
	VECTOR pos;
	VECTOR centorPos;//中心座標

	std::vector<VERTEX3D> vertex;
	std::vector<unsigned short> indices;
	std::vector<VERTEX3D> verts;
	MATRIX rollingMat;
	MATRIX mixMat;

	int moveCnt;

	//Debug用
	bool flg;
	bool flg2;
};

