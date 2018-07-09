#pragma once
#include "Dxlib.h"

class Cube {
public:
	Cube();
	~Cube();

	void Updata();
	void Draw();
private:
	VERTEX3D vertex[3];
	int cubeH;
};

