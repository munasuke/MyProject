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

//�L���[�u�Ǘ�
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

	//���
	void WaitUpdata();//�ҋ@��
	void RollingUpdata();//��]��
	void RolledUpdata();//��]��A�d�S�Čv�Z
	void FallingUpdata();//������
	void(Cube::*updata)();//��ԑJ�ڗp�����o�֐��|�C���^

	VECTOR SetCentorPos(std::vector<VERTEX3D> ver);//���S�_�����߂�

	int cubeH;
	VECTOR angle;
	VECTOR pos;
	VECTOR centorPos;//���S���W
	VECTOR velocity;

	std::vector<VERTEX3D> vertex;
	std::vector<unsigned short> indices;
	std::vector<VERTEX3D> verts;
	MATRIX rollingMat;
	MATRIX mixMat;

	int moveCnt;
	int waitTime;//�ҋ@����
	bool waitFlag;//�ҋ@�t���O(true:�ҋ@, false:�s��)
	MATERIALPARAM mt;
	int impactH;

	//Debug�p
	bool flg;
	bool flg2;
};

