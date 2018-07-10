#include "Cube.h"
#include <vector>

namespace{
	const float cube_len = 5.0f;
	VERTEX3D originalVertex[3] = {
		{ VGet(0.0f, 10.0f, 0.0f),	VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.5f, 0.0f, 0.0f, 0.0f },
		{ VGet(-5.0f, 0.0f, 0.0f),	VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f },
		{ VGet(5.0f, 0.0f, 0.0f),	VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 1.0f, 1.0f, 0.0f, 0.0f }
	};
}

Cube::Cube() :
	cubeH(LoadGraph("img/cube_tex.png")),
	angle(0.1f),
	pos(VGet(0.0f, 0.0f, 0.0f))
{
}


Cube::~Cube() {
}

void Cube::Updata() {
}

void Cube::Draw() {
	for (int z = -1; z < 10; z++){
		for (int x = -5; x < 5; x++){
			if (!CheckCameraViewClip_Box(VGet(-cube_len * x, 0, -cube_len * z), VGet(cube_len * x, -2 * cube_len, cube_len * z))){
				DrawCube3D(VGet(-cube_len * x, 0, -cube_len * z), VGet(cube_len * x, -2 * cube_len, cube_len * z), GetColor(0, 255 - x, 0), 0xffffff, true);
			}
		}
	}

	//‰ñ“]s—ñ‚Ìì¬
	MATRIX rot = MGetRotY(angle);

	//•½sˆÚ“®s—ñ‚Ìì¬
	MATRIX translate = MGetTranslate(pos);

	if (CheckHitKey(KEY_INPUT_Z)){
		pos.x -= 0.1f;
	}
	if (CheckHitKey(KEY_INPUT_X)){
		pos.x += 0.1f;
	}

	//s—ñ‚ÌæŽZ
	MATRIX mix = MMult(translate, rot);
	angle += 0.1;
	std::vector<VERTEX3D> verts(originalVertex, originalVertex + 3);

	for (auto& v : verts){
		v.pos = VTransform(v.pos, mix);
	}

	DrawPolygon3D(verts.data(), 1, cubeH, false);
}
