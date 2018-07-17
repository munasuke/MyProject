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
	std::vector<VERTEX3D> verts;
}

Cube::Cube() :
	updata(&Cube::WaitUpdata),
	cubeH(LoadGraph("img/cube_tex.png")),
	angle(0.0f),
	pos(VGet(0.0f, ed_w/2, 0.0f)),
	centorPos(pos)
{
	//���ʂ̕`����s��Ȃ�
	SetUseBackCulling(false);

	vertex.resize(6 * _countof(originalVertex));
	indices.resize(6 * _countof(originalIndex));

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

	verts = { vertex.begin(), vertex.end() };
	auto m = MGetTranslate(VGet(0.0f, ed_w / 2, 0.0f));
	for (auto& v : verts){
		v.pos = VTransform(v.pos, m);
	}

	//Debug�p
	flg = true;
	flg2 = true;
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
	MATRIX translate = MGetTranslate(centorPos);

	//�s��̏�Z
	//���_�Ɉړ������ĉ�]�A�����č��W��߂�
	MATRIX mix = MMult(rot, MGetTranslate(VGet(-centorPos.x, -centorPos.y, -centorPos.z)));

	mix = MMult(rot, translate);

	//for (auto& v : verts){
	//	//���W����]
	//	v.pos = VTransform(v.pos, mix);
	//	//�@������]
	//	v.norm = VTransformSR(v.norm, mix);//SR : Scaling + Rotation
	//}

	DrawPolygonIndexed3D(verts.data(), verts.size(), indices.data(), indices.size()/3, cubeH, false);

	SetUseZBuffer3D(false);
	SetWriteZBuffer3D(false);
	DrawSphere3D(centorPos, 1.0f, 10, 0xff0000, 0xff0000, true);//�L���[�u�̒��S�_
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
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
		rot2 = MGetRotX(i == 4 ? 90.0f * DX_PI_F / 180.0f : 270.0f * DX_PI_F / 180.0f);
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
	centorPos.x += x * ed_w / 2.0f;
	centorPos.z += z * ed_w / 2.0f;
	centorPos.y -= ed_w / 2.0f;
	updata = &Cube::RollingUpdata;
}

void Cube::WaitUpdata() {
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		flg = false;
		updata = &Cube::RollStartUpdata;
	}
}

void Cube::RollStartUpdata() {
	centorPos.z -= ed_w / 2;
	centorPos.y -= ed_w / 2;
	updata = &Cube::RollingUpdata;
}

void Cube::RollingUpdata() {
	if (!flg) {
		angle -= 0.01f;
		if (angle < -1.55f) {
			flg = true;
			angle = -1.55f;
			//updata = &Cube::RolledUpdata;
		}
	}
}

void Cube::RolledUpdata() {
	if (flg2) {
		flg2 = false;
		centorPos.z -= ed_w / 2;
		centorPos.y += ed_w / 2;
		pos = centorPos;
	}
	else {
		flg2 = true;
		updata = &Cube::WaitUpdata;
	}
	angle = 0.0f;
}
