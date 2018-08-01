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

//�L���[�u�Ǘ�
class Cube {
public:
	Cube(VECTOR _pos, VECTOR _scale = {1.0f, 1.0f, 1.0f});
	virtual ~Cube();

	void Updata();
	void Draw();

	void RollOver(float x, float z);
protected:
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

	//Debug�p
	bool flg;
	bool flg2;
};

