#include "Cube.h"
#include <cassert>

namespace{
	//1�ӂ̒���
	const float cube_ed = 5.0f;
	const float ed_w = 10.0f;

	//�ʂ̑���
	const int surface_max = 6;

	//1�ʂɕK�v�Ȓ��_���
	VERTEX3D originalVertex[] = {
		{ VGet(-ed_w/2,  ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f },
		{ VGet( ed_w/2,  ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 2.0f, 0.0f, 0.0f, 0.0f },
		{ VGet(-ed_w/2, -ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 2.0f, 0.0f, 0.0f },
		{ VGet( ed_w/2, -ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 2.0f, 2.0f, 0.0f, 0.0f },
	};

	VERTEX3D originalVertex2[] = {
		{ VGet(-ed_w/2,  ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f },
		{ VGet( ed_w/2,  ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 2.0f, 0.0f, 0.0f, 0.0f },
		{ VGet(-ed_w/2, -ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 2.0f, 0.0f, 0.0f },
		{ VGet( ed_w/2, -ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 2.0f, 2.0f, 0.0f, 0.0f },
	};

	//1�ʂɕK�v�ȃC���f�b�N�X���i���v���ɐݒ�j
	unsigned short originalIndex[] = {
		0, 1, 2, 
		1, 3, 2
	};
}

Cube::Cube() :
	updata(&Cube::WaitUpdata),
	cubeH(LoadGraph("img/cube_tex.png")),
	angle(0.0f),
	pos(VGet(0.0f, ed_w/2, 0.0f)),
	centorPos(pos),
	moveCnt(0)
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

	vertex2.resize(6 * _countof(originalVertex2));
	//Cube�̒��_���ƃC���f�b�N�X���̐ݒ�
	SetUpPolygon();
	//�y��
	pos2 = { 0.0f, ed_w / 2, 0.0f };
	verts2 = { vertex2.begin(), vertex2.end() };

	verts = { vertex.begin(), vertex.end() };
	rollingMat = MGetTranslate(VGet(0.0f, ed_w / 2, 0.0f));
	for (auto& v : verts){
		v.pos = VTransform(v.pos, rollingMat);
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
	//for (int z = -1; z < 10; z++){
	//	for (int x = -5; x < 5; x++){
	//		if (!CheckCameraViewClip_Box(VGet(-cube_ed * x, 0, -cube_ed * z), VGet(cube_ed * x, -2 * cube_ed, cube_ed * z))){
	//			DrawCube3D(VGet(-cube_ed * x, 0, -cube_ed * z), VGet(cube_ed * x, -2 * cube_ed, cube_ed * z), GetColor(0, 255 - x, 0), 0xffffff, true);
	//		}
	//	}
	//}

	//4x5
	//for (int i = 0; i < 5; i++){
	//	for (int j = 0; j < 4; j++){
	//		
	//	}
	//}
	//DrawPolygonIndexed3D(verts.data(), static_cast<int>(verts.size()), indices.data(), static_cast<int>(indices.size())/3, cubeH, false);

	MATRIX matrix = MGetTranslate(pos2);
	for (auto& m : verts2){
		m.pos = VTransform(m.pos, matrix);
		m.norm = VTransformSR(m.norm, matrix);
	}
	DrawPolygonIndexed3D(verts2.data(), static_cast<int>(verts2.size()), indices.data(), static_cast<int>(indices.size())/3, cubeH, false);
}

void Cube::RollOver(float x, float z) {
	if (updata != &Cube::WaitUpdata){
		return;
	}

	//(x, z) = (1, 0), (-1, 0), (0, 1), (0, -1)
	assert(((x == 1 || x == -1) && z == 0) || (x == 0 && (z == 1 || z == -1)));

	//���S�_�����炷
	centorPos.x += x * ed_w / 2.0f;
	centorPos.z += z * ed_w / 2.0f;
	centorPos.y -= ed_w / 2.0f;

	//�p���x�̐ݒ�
	float omegaX = z * (DX_PI_F / 2.0f) / CNT_MAX;
	float omegaZ = -x * (DX_PI_F / 2.0f) / CNT_MAX;

	//���_�֕��s�ړ�����]�����s�ړ��̍s��
	rollingMat = MGetTranslate(VScale(centorPos, -1.0f));
	rollingMat = MMult(rollingMat, MGetRotX(omegaX));
	rollingMat = MMult(rollingMat, MGetRotZ(omegaZ));
	rollingMat = MMult(rollingMat, MGetTranslate(centorPos));

	updata = &Cube::RollingUpdata;
}

void Cube::SetUpPolygon() {
	static MATRIX rot2 = MGetIdent();
	//����
	//for (int i = 0; i < surface_max - 2; ++i){
	//	rot2 = MGetRotY(static_cast<float>(i) * DX_PI_F / 2.0f);
	//	for (int j = 0; j < _countof(originalVertex); ++j){
	//		vertex[i * _countof(originalVertex) + j] = originalVertex[j];
	//		vertex[i * _countof(originalVertex) + j].pos = VTransform(originalVertex[j].pos, rot2);
	//		vertex[i * _countof(originalVertex) + j].norm = VTransformSR(originalVertex[j].norm, rot2);
	//	}
	//	for (int j = 0; j < _countof(originalIndex); ++j){
	//		indices[i * _countof(originalIndex) + j] = originalIndex[j] + static_cast<unsigned short>((i * _countof(originalVertex)));
	//	}
	//}
	for (int i = 0; i < surface_max - 2; ++i){
		rot2 = MGetRotY(static_cast<float>(i) * DX_PI_F / 2.0f);
		for (int j = 0; j < _countof(originalVertex2); ++j){
			vertex2[i * _countof(originalVertex2) + j] = originalVertex2[j];
			vertex2[i * _countof(originalVertex2) + j].pos = VTransform(originalVertex2[j].pos, rot2);
			vertex2[i * _countof(originalVertex2) + j].norm = VTransformSR(originalVertex2[j].norm, rot2);
		}
		for (int j = 0; j < _countof(originalIndex); ++j){
			indices[i * _countof(originalIndex) + j] = originalIndex[j] + static_cast<unsigned short>((i * _countof(originalVertex2)));
		}
	}
	//�W�ƒ�
	//for (int i = 4; i < surface_max; ++i){
	//	rot2 = MGetRotX(static_cast<float>((1 + i * 2)) * (DX_PI_F / 2.0f));
	//	for (int j = 0; j < _countof(originalVertex); ++j){
	//		vertex[i * _countof(originalVertex) + j] = originalVertex[j];
	//		vertex[i * _countof(originalVertex) + j].pos = VTransform(originalVertex[j].pos, rot2);
	//		vertex[i * _countof(originalVertex) + j].norm = VTransformSR(originalVertex[j].norm, rot2);
	//	}
	//	for (int j = 0; j < _countof(originalIndex); ++j){
	//		indices[i * _countof(originalIndex) + j] = originalIndex[j] + static_cast<unsigned short>((i * _countof(originalVertex)));
	//	}
	//}
	for (int i = 4; i < surface_max; ++i){
		rot2 = MGetRotX(static_cast<float>((1 + i * 2)) * (DX_PI_F / 2.0f));
		for (int j = 0; j < _countof(originalVertex2); ++j){
			vertex2[i * _countof(originalVertex2) + j] = originalVertex2[j];
			vertex2[i * _countof(originalVertex2) + j].pos = VTransform(originalVertex2[j].pos, rot2);
			vertex2[i * _countof(originalVertex2) + j].norm = VTransformSR(originalVertex2[j].norm, rot2);
		}
		for (int j = 0; j < _countof(originalIndex); ++j){
			indices[i * _countof(originalIndex) + j] = originalIndex[j] + static_cast<unsigned short>((i * _countof(originalVertex2)));
		}
	}
}

//�ҋ@��
void Cube::WaitUpdata() {
	//�Ȃɂ����Ȃ���
}

//��]��
void Cube::RollingUpdata() {
	for (auto& v : verts){
		//���W����]
		v.pos = VTransform(v.pos, rollingMat);
		//�@������]
		v.norm = VTransformSR(v.norm, rollingMat);//SR : Scaling + Rotation
	}
	moveCnt++;
	if (moveCnt >= CNT_MAX){
		moveCnt = 0;
		updata = &Cube::RolledUpdata;
	}
}

//��]��
void Cube::RolledUpdata() {
	centorPos = SetCentorPos(verts);
	updata = &Cube::WaitUpdata;
}

//���S�_���Čv�Z
VECTOR Cube::SetCentorPos(std::vector<VERTEX3D> ver) {
	//24���_�𑫂��ĕ��ς��o��
	VECTOR ret = { 0, 0, 0 };
	for (auto& v : ver){
		ret = VAdd(ret, v.pos);
	}
	float div = 1.0f / static_cast<float>(ver.size());
	return VScale(ret, div);
}
