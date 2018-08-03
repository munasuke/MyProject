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

Cube::Cube()
{
}

Cube::Cube(VECTOR _pos, VECTOR _scale, COLOR_F _color) :
	updata(&Cube::WaitUpdata),
	cubeH(LoadGraph("img/cube_tex.png")),
	angle({ 0.0f, 0.0f, 0.0f }),
	pos(_pos),
	centorPos(pos),
	velocity({0.0f, 0.0f, 0.0f}),
	moveCnt(0),
	waitTime(maxWaitTime),
	waitFlag(true),
	impactH(LoadSoundMem("se/zushin.mp3"))
{

	//���ʂ̕`����s��Ȃ�
	SetUseBackCulling(false);

	vertex.resize(6 * _countof(originalVertex));
	indices.resize(6 * _countof(originalIndex));

	//�}�e���A���̐ݒ�
	SetMaterialUseVertDifColor(false);
	mt= MATERIALPARAM();
	mt.Ambient		= _color;
	mt.Diffuse		= _color.r != 0.0f ? GetColorF(0.75f, 0.75f, 0.75f, 1.0f) : GetColorF(0.4f, 0.4f, 0.4f, 1.0f);
	mt.Specular		= GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	mt.Emissive		= _color.r != 0.0f ? GetColorF(0.2f, 0.2f, 0.2f, 0.2f) : GetColorF(0.0f, 0.0f, 0.0f, 0.2f);
	mt.Power		= 10.0f;

	//Cube�̒��_���ƃC���f�b�N�X���̐ݒ�
	SetUpPolygon();

	//�L���[�u�̏����z�u
	verts = { vertex.begin(), vertex.end() };
	rollingMat = MGetTranslate(pos);
	for (auto& v : verts){
		v.pos = VTransform({ v.pos.x * _scale.x, v.pos.y * _scale.y, v.pos.z * _scale.z }, rollingMat);
	}

	//UV�̐ݒ�
	for (int i = 0; i < 6; i++) {
		float u = VSize(VSub(verts[i * 4 + 1].pos, verts[i * 4 + 0].pos)) / (ed_w * 2);
		float v = VSize(VSub(verts[i * 4 + 2].pos, verts[i * 4 + 0].pos)) / (ed_w * 2);
		for (int j = 0; j < 4; j++) {
			verts[i * 4 + j].u *= u;
			verts[i * 4 + j].v *= v;
		}
	}

	velocity.x = static_cast<float>(GetRand(200) - 100) / 1000.0f;
	velocity.z = static_cast<float>(GetRand(100)) / 1000.0f;

	angle = {
		static_cast<float>(DxLib::GetRand(2000) - 1000) / 100000.0f,
		static_cast<float>(DxLib::GetRand(2000) - 1000) / 100000.0f,
		static_cast<float>(DxLib::GetRand(2000) - 1000) / 100000.0f
	};

	//Debug�p
	flg = true;
	flg2 = true;
}


Cube::~Cube() {
}

void Cube::Updata() {
	if (waitFlag) {
		if (waitTime <= 0) {
			waitFlag = false;
			waitTime = maxWaitTime;
		}
		waitTime--;
	}
	else {
		RollOver(0.0f, -1.0f);
	}

	if (centorPos.z <= -60.0f) {
		if (updata != &Cube::FallingUpdata) {
			updata = &Cube::FallingUpdata;
		}
	}

	(this->*updata)();
}

void Cube::Draw() {
	SetMaterialParam(mt);
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

float Cube::GetPosition()
{
	return centorPos.z;
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
	PlaySoundMem(impactH, DX_PLAYTYPE_BACK);
	centorPos = SetCentorPos(verts);
	waitFlag = true;
	updata = &Cube::WaitUpdata;
}

//������
void Cube::FallingUpdata()
{
	velocity.y -= 0.01f;

	MATRIX mt = MGetTranslate(VSub(VGet(0.0f, 0.0f, 0.0f), centorPos));

	mt = MMult(mt, MGetRotX(angle.x));
	mt = MMult(mt, MGetRotY(angle.y));
	mt = MMult(mt, MGetRotZ(angle.z));

	mt = MMult(mt, MGetTranslate(centorPos));
	mt = MMult(mt, MGetTranslate(velocity));

	for (auto& v : verts) {
		v.pos = VTransform(v.pos, mt);
		v.norm = VTransformSR(v.norm, mt);
	}
	centorPos = SetCentorPos(verts);
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
