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

	//���
	void WaitUpdata();//�ҋ@��
	void RollingUpdata();//��]��
	void RolledUpdata();//��]��A�d�S�Čv�Z

	int cubeH;
	float angle;
	VECTOR pos;
};

