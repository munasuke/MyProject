#pragma once
#include "Dxlib.h"

enum Direction{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

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
	void RollStartUpdata();//��]���鎲�����߂�
	void RollingUpdata();//��]��
	void RolledUpdata();//��]��A�d�S�Čv�Z
	void(Cube::*updata)();//��ԑJ�ڗp�����o�֐��|�C���^

	VECTOR SetCentorPos();

	int cubeH;
	float angle;
	VECTOR pos;
	VECTOR centorPos;//���S���W

	//Debug�p
	bool flg;
	bool flg2;
};

