#pragma once
#include "Dxlib.h"

class Cube {
public:
	Cube();
	~Cube();

	void Updata();
	void Draw();
private:
	void SetUpPolygon();
	void RollOver(float x, float z);

	//状態
	void WaitUpdata();//待機中
	void RollingUpdata();//回転中
	void RolledUpdata();//回転後、重心再計算
	void(Cube::*updata)();//状態遷移用メンバ関数ポインタ

	int cubeH;
	float angle;
	VECTOR pos;
};

