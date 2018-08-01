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

	//1�ʂɕK�v�ȃC���f�b�N�X���i���v���ɐݒ�j
	unsigned short originalIndex[] = {
		0, 1, 2, 
		1, 3, 2
	};
}

Cube::Cube(VECTOR _pos, VECTOR _scale) :
	updata(&Cube::WaitUpdata),
	cubeH(LoadGraph("img/cube_tex.png")),
	angle(0.0f),
	pos(_pos),
	centorPos(pos),
	moveCnt(0)
{

	//���ʂ̕`����s��Ȃ�
	SetUseBackCulling(false);

	vertex.resize(6 * _countof(originalVertex));
	indices.resize(6 * _countof(originalIndex));

	//�}�e���A���̐ݒ�
	MATERIALPARAM mt= MATERIALPARAM();
	mt.Ambient		= GetColorF(0.2f, 0.2f, 0.2f, 1.0f);
	mt.Diffuse		= GetColorF(0.75f, 0.75f, 0.75f, 1.0f);
	mt.Specular		= GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	mt.Emissive		= GetColorF(0.2f, 0.2f, 0.2f, 0.2f);
	mt.Power		= 10.0f;
	SetMaterialParam(mt);

	//Cube�̒��_���ƃC���f�b�N�X���̐ݒ�
	SetUpPolygon();

	verts = { vertex.begin(), vertex.end() };
	rollingMat = MGetTranslate(pos);
	for (auto& v : verts){
		v.pos = VTransform({ v.pos.x * _scale.x, v.pos.y * _scale.y, v.pos.z * _scale.z }, rollingMat);
		//v.norm = VTransformSR({ v.pos.x * _scale.x, v.pos.y * _scale.y, v.pos.z * _scale.z }, rollingMat);
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
	DrawPolygonIndexed3D(verts.data(), static_cast<int>(verts.size()), indices.data(), static_cast<int>(indices.size())/3, cubeH, false);
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
	for (int i = 0; i < surface_max - 2; ++i){
		rot2 = MGetRotY(static_cast<float>(i) * DX_PI_F / 2.0f);
		for (int j = 0; j < _countof(originalVertex); ++j){
			vertex[i * _countof(originalVertex) + j] = originalVertex[j];
			vertex[i * _countof(originalVertex) + j].pos = VTransform(originalVertex[j].pos, rot2);
			vertex[i * _countof(originalVertex) + j].norm = VTransformSR(originalVertex[j].norm, rot2);
		}
		for (int j = 0; j < _countof(originalIndex); ++j){
			indices[i * _countof(originalIndex) + j] = originalIndex[j] + static_cast<unsigned short>((i * _countof(originalVertex)));
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
			indices[i * _countof(originalIndex) + j] = originalIndex[j] + static_cast<unsigned short>((i * _countof(originalVertex)));
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
