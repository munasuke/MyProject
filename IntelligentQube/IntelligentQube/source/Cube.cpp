#include "Cube.h"

namespace{
	const float cube_len = 5.0f;
}

Cube::Cube() :
	cubeH(LoadGraph("img/cube_tex.png"))
{
	//vertex[3] = {
	//	{VGet(0.0f, 10.0f, 0.0f), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f},
	//	{VGet(2.0f, 10.0f - 4.0f, 0.0f), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 1.0f, 0.0f, 0.0f, 0.0f},
	//	{VGet(-1.0f, 10.0f - 4.0f, 0.0f), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 1.0f, 1.0f, 0.0f, 0.0f}
	//};
}


Cube::~Cube() {
}

void Cube::Updata() {
}

void Cube::Draw() {
	//DrawPolygon3D(vertex, 1, cubeH, false);
	for (int z = -1; z < 10; z++){
		for (int x = -5; x < 5; x++){
			DrawCube3D(VGet(-cube_len * x, 0, -cube_len * z), VGet(cube_len * x, -2 * cube_len, cube_len * z), 0x00ff00, 0xffffff, true);
		}
	}
}
