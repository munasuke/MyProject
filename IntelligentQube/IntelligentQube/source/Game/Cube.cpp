#include "Cube.h"
#include <cassert>

namespace{
	//1辺の長さ
	const float cube_ed = 5.0f;
	const float ed_w = 10.0f;

	//面の総数
	const int surface_max = 6;

	//1面に必要な頂点情報
	VERTEX3D originalVertex[] = {
		{ VGet(-ed_w/2,  ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f },
		{ VGet( ed_w/2,  ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 2.0f, 0.0f, 0.0f, 0.0f },
		{ VGet(-ed_w/2, -ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 0.0f, 2.0f, 0.0f, 0.0f },
		{ VGet( ed_w/2, -ed_w/2, -ed_w/2), VGet(0.0f, 0.0f, -1.0f), GetColorU8(255, 255, 255, 255), GetColorU8(255, 255, 255, 255), 2.0f, 2.0f, 0.0f, 0.0f },
	};

	//1面に必要なインデックス情報（時計回りに設定）
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

	//裏面の描画を行わない
	SetUseBackCulling(false);

	vertex.resize(6 * _countof(originalVertex));
	indices.resize(6 * _countof(originalIndex));

	//マテリアルの設定
	SetMaterialUseVertDifColor(false);
	mt= MATERIALPARAM();
	mt.Ambient		= _color;
	mt.Diffuse		= _color.r != 0.0f ? GetColorF(0.75f, 0.75f, 0.75f, 1.0f) : GetColorF(0.4f, 0.4f, 0.4f, 1.0f);
	mt.Specular		= GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	mt.Emissive		= _color.r != 0.0f ? GetColorF(0.2f, 0.2f, 0.2f, 0.2f) : GetColorF(0.0f, 0.0f, 0.0f, 0.2f);
	mt.Power		= 10.0f;

	//Cubeの頂点情報とインデックス情報の設定
	SetUpPolygon();

	//キューブの初期配置
	verts = { vertex.begin(), vertex.end() };
	rollingMat = MGetTranslate(pos);
	for (auto& v : verts){
		v.pos = VTransform({ v.pos.x * _scale.x, v.pos.y * _scale.y, v.pos.z * _scale.z }, rollingMat);
	}

	//UVの設定
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

	//Debug用
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

	//中心点をずらす
	centorPos.x += x * ed_w / 2.0f;
	centorPos.z += z * ed_w / 2.0f;
	centorPos.y -= ed_w / 2.0f;

	//角速度の設定
	float omegaX = z * (DX_PI_F / 2.0f) / CNT_MAX;
	float omegaZ = -x * (DX_PI_F / 2.0f) / CNT_MAX;

	//原点へ平行移動→回転→平行移動の行列
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
	//側面
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
	//蓋と底
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

//待機中
void Cube::WaitUpdata() {
	//なにもしないよ
}

//回転中
void Cube::RollingUpdata() {
	for (auto& v : verts){
		//座標を回転
		v.pos = VTransform(v.pos, rollingMat);
		//法線を回転
		v.norm = VTransformSR(v.norm, rollingMat);//SR : Scaling + Rotation
	}
	moveCnt++;
	if (moveCnt >= CNT_MAX){
		moveCnt = 0;
		updata = &Cube::RolledUpdata;
	}
}

//回転後
void Cube::RolledUpdata() {
	PlaySoundMem(impactH, DX_PLAYTYPE_BACK);
	centorPos = SetCentorPos(verts);
	waitFlag = true;
	updata = &Cube::WaitUpdata;
}

//落下中
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

//中心点を再計算
VECTOR Cube::SetCentorPos(std::vector<VERTEX3D> ver) {
	//24頂点を足して平均を出す
	VECTOR ret = { 0, 0, 0 };
	for (auto& v : ver){
		ret = VAdd(ret, v.pos);
	}
	float div = 1.0f / static_cast<float>(ver.size());
	return VScale(ret, div);
}
