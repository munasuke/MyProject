#pragma once
#include "Dxlib.h"
#include <vector>

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

	void RollOver(float x, float z);
private:
	void SetUpPolygon();

	//���
	void WaitUpdata();//�ҋ@��
	void RollingUpdata();//��]��
	void RolledUpdata();//��]��A�d�S�Čv�Z
	void(Cube::*updata)();//��ԑJ�ڗp�����o�֐��|�C���^

	VECTOR SetCentorPos(std::vector<VERTEX3D> ver);//���S�_�����߂�

	int cubeH;
	float angle;
	VECTOR pos;
	VECTOR centorPos;//���S���W

	std::vector<VERTEX3D> vertex;
	std::vector<unsigned short> indices;
	std::vector<VERTEX3D> verts;
	MATRIX rollingMat;
	MATRIX mixMat;

	int moveCnt;
	//float omegaX;//X����]�̊p���x
	//float omegaZ;//Z����]�̊p���x

	//Debug�p
	bool flg;
	bool flg2;
};

