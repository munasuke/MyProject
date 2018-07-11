#include "Cube.h"
#include <vector>

namespace{
	//�ӂ̒���
	const float cube_ed = 5.0f;
	const float ed_w = 10.0f;

	//���_���
	VERTEX3D originalVertex[] = {
		//�@
		{ VGet(-ed_w/2,  ed_w, -ed_w/2),	VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f },
		{ VGet( ed_w/2,  ed_w, -ed_w/2),	VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 1.0f, 0.0f, 0.0f, 0.0f },
		{ VGet(-ed_w/2, -ed_w, -ed_w/2),	VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 1.0f, 0.0f, 0.0f },
		{ VGet( ed_w/2, -ed_w, -ed_w/2),	VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 1.0f, 1.0f, 0.0f, 0.0f }
	};

	//�C���f�b�N�X���i���v���ɐݒ�j
	unsigned short originalIndex[] = {
		//�@
		0, 1, 2, 1, 3, 2
	};

	std::vector<unsigned short> indices;
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
			if (!CheckCameraViewClip_Box(VGet(-cube_ed * x, 0, -cube_ed * z), VGet(cube_ed * x, -2 * cube_ed, cube_ed * z))){
				DrawCube3D(VGet(-cube_ed * x, 0, -cube_ed * z), VGet(cube_ed * x, -2 * cube_ed, cube_ed * z), GetColor(0, 255 - x, 0), 0xffffff, true);
			}
		}
	}

	//��]�s��̍쐬
	MATRIX rot = MGetRotY(angle);

	//���s�ړ��s��̍쐬
	MATRIX translate = MGetTranslate(pos);

	if (CheckHitKey(KEY_INPUT_Z)){
		pos.x -= 0.1f;
	}
	if (CheckHitKey(KEY_INPUT_X)){
		pos.x += 0.1f;
	}

	//�s��̏�Z
	MATRIX mix = MMult(rot, translate);
	angle += 0.01;
	std::vector<VERTEX3D> verts(originalVertex, originalVertex + _countof(originalVertex));

	for (auto& v : verts){
		//���W����]
		v.pos = VTransform(v.pos, mix);
		//�@������]
		v.norm = VTransformSR(v.norm, mix);//SR : Scaling + Rotation
	}

	DrawPolygonIndexed3D(verts.data(), verts.size(), originalIndex, 2, cubeH, false);
}
