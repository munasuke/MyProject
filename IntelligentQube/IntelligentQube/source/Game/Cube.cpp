#include "Cube.h"
#include <vector>

namespace{
	//�ӂ̒���
	const float cube_ed = 5.0f;
	const float ed_w = 10.0f;

	//�ʂ̑���
	const int surface_max = 6;

	//���_���
	VERTEX3D originalVertex[] = {
		{ VGet(-ed_w/2,  ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f },
		{ VGet( ed_w/2,  ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 1.0f, 0.0f, 0.0f, 0.0f },
		{ VGet(-ed_w/2, -ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 1.0f, 0.0f, 0.0f },
		{ VGet( ed_w/2, -ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 1.0f, 1.0f, 0.0f, 0.0f },
	};

	//�C���f�b�N�X���i���v���ɐݒ�j
	unsigned short originalIndex[] = {
		0, 1, 2, 
		1, 3, 2
	};
	std::vector<VERTEX3D> vertex;
	std::vector<unsigned short> indices;
}

Cube::Cube() :
	updata(&Cube::WaitUpdata),
	cubeH(LoadGraph("img/cube_tex.png")),
	angle(0.1f),
	pos(VGet(0.0f, 10.0f, 0.0f))
{
	vertex.resize(6 * _countof(originalVertex));//���_��
	indices.resize(6 * _countof(originalIndex));//�C���f�b�N�X��

	//�}�e���A���̐ݒ�
	MATERIALPARAM mt = MATERIALPARAM();
	mt.Ambient = GetColorF(0.2f, 0.2f, 0.2f, 1.0f);
	mt.Diffuse = GetColorF(0.75f, 0.75f, 0.75f, 1.0f);
	mt.Specular = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	mt.Emissive = GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
	mt.Power = 10.0f;
	SetMaterialParam(mt);

	//Cube�̒��_���ƃC���f�b�N�X���̐ݒ�
	SetUpPolygon();
}


Cube::~Cube() {
}

void Cube::Updata() {
	(this->*updata)();
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
	MATRIX rot = MGetRotX(angle);

	//���s�ړ��s��̍쐬
	MATRIX translate = MGetTranslate(pos);

	//�s��̏�Z
	MATRIX mix = MMult(rot, translate);

	if (CheckHitKey(KEY_INPUT_Z)) {
		pos.x -= 0.1f;
	}
	if (CheckHitKey(KEY_INPUT_X)) {
		pos.x += 0.1f;
	}

	angle += 0.01;


	std::vector<VERTEX3D> verts(vertex.begin(), vertex.end());

	for (auto& v : verts){
		//���W����]
		v.pos = VTransform(v.pos, mix);
		//�@������]
		v.norm = VTransformSR(v.norm, mix);//SR : Scaling + Rotation
	}

	DrawPolygonIndexed3D(verts.data(), verts.size(), indices.data(), indices.size()/3, cubeH, false);
}

void Cube::SetUpPolygon() {
	static MATRIX rot2 = MGetIdent();
	//����
	for (int i = 0; i < surface_max - 2; ++i){
		rot2 = MGetRotY(static_cast<float>(i) * DX_PI_F / 2.0f);
		for (int j = 0; j < _countof(originalVertex); ++j){
			vertex[i * _countof(originalVertex) + j] = originalVertex[j];
			vertex[i * _countof(originalVertex) + j].pos = VTransform(originalVertex[j].pos, rot2);
			vertex[i * _countof(originalVertex) + j].norm = VTransformSR(originalVertex[j].norm, rot2);
		}
		for (int j = 0; j < _countof(originalIndex); ++j){
			indices[i * _countof(originalIndex) + j] = originalIndex[j] + (i * _countof(originalVertex));
		}
	}
	//�W�ƒ�
	for (int i = 4; i < surface_max; ++i){
		rot2 = MGetRotX(static_cast<float>((1 + i * 2)) * (DX_PI_F / 2.0f));
		for (int j = 0; j < _countof(originalVertex); ++j){
			vertex[i * _countof(originalVertex) + j] = originalVertex[j];
			vertex[i * _countof(originalVertex) + j].pos = VTransform(originalVertex[j].pos, rot2);
			vertex[i * _countof(originalVertex) + j].norm = VTransformSR(originalVertex[j].norm, rot2);
		}
		for (int j = 0; j < _countof(originalIndex); ++j){
			indices[i * _countof(originalIndex) + j] = originalIndex[j] + (i * _countof(originalVertex));
		}
	}
}

void Cube::RollOver(float x, float z) {

}

void Cube::WaitUpdata() {
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		updata = &Cube::RolledUpdata;
	}
}

void Cube::RollingUpdata() {
}

void Cube::RolledUpdata() {
}