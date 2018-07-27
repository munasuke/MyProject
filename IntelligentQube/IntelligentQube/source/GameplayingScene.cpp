#include "GameplayingScene.h"
#include "Game.h"
#include "NowLoading.h"
#include "Player.h"
#include "Game/Cube.h"


GameplayingScene::GameplayingScene(std::weak_ptr<KeyInput> _key) : 
	camPos(0.0f, 30.0f, -35.0f),
	targetPos(0.0f, 10.0f, 0.0f)
{
	key = _key;
	alpha = 0;
	alphaFlg = false;

	ld = std::make_shared<NowLoading>();
	pl = std::make_shared<Player>(key);
	cube = std::make_shared<Cube>();
	toEyeVector = VSub(VGet(camPos.x, camPos.y, camPos.z), VGet(targetPos.x, targetPos.y, targetPos.z));

	//�J�����̐ݒ�
	SetupCamera_Perspective(RAD(90.0f));//���ߖ@�J�����̐ݒ�
	SetCameraNearFar(0.5f, 300.0f);//�N���b�v�̐ݒ�

	//���C�g�̐ݒ�
	SetLightEnable(true);
	SetUseLighting(true);
	//���C�g�̕����Ƒ����̐ݒ�
	SetLightDirection(VGet(1.0f, 1.0f, 1.0f));//���s�����x�N�g��
	SetLightDifColor(GetColorF(0.8f, 0.8f, 0.8f, 1.0f));//�f�B�t���[�Y
	SetLightAmbColor(GetColorF(0.4f, 0.4f, 0.4f, 1.0f));//�A���r�G���g
	SetLightSpcColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));//�X�y�L�����[

	printf("Gameplaying Scene\n");
}


GameplayingScene::~GameplayingScene()
{
	printf("Gameplaying Scene is Deleted\n\n");
}

void GameplayingScene::Updata()
{

	if (key.lock()->IsTrigger(PAD_INPUT_10)){
		alphaFlg = true;
	}
	//�L���[�u����
	if (key.lock()->IsTrigger(PAD_INPUT_8)){
		cube->RollOver(0, 1);
	}
	if (key.lock()->IsTrigger(PAD_INPUT_5)){
		cube->RollOver(0, -1);
	}
	if (key.lock()->IsTrigger(PAD_INPUT_6)){
		cube->RollOver(1, 0);
	}
	if (key.lock()->IsTrigger(PAD_INPUT_4)){
		cube->RollOver(-1, 0);
	}
	pl->Updata();
	cube->Updata();

	FadeOut();
}

void GameplayingScene::Draw()
{
	auto plPos = pl->GetPosition();
	auto eye = PlusVECTOR(plPos, toEyeVector);
	
	if (CheckHitKey(KEY_INPUT_LSHIFT)) {
		if (key.lock()->IsTrigger(PAD_INPUT_1)) {
			CameraRotation(&eye.x, &eye.z, +90.0f * DX_PI_F / 180.0f, pl->GetPosition().x, pl->GetPosition().z);
		}
		else if (key.lock()->IsTrigger(PAD_INPUT_2)) {
			CameraRotation(&eye.x, &eye.z, -90.0f * DX_PI_F / 180.0f, pl->GetPosition().x, pl->GetPosition().z);
		}
	}
	else {
		if (key.lock()->IsPressing(PAD_INPUT_1)) {
			CameraRotation(&eye.x, &eye.z, +Angle, pl->GetPosition().x, pl->GetPosition().z);
		}
		if (key.lock()->IsPressing(PAD_INPUT_2)) {
			CameraRotation(&eye.x, &eye.z, -Angle, pl->GetPosition().x, pl->GetPosition().z);
		}
		if (key.lock()->IsPressing(PAD_INPUT_3)) {
			camPos = { 0.0f, 15.0f, -25.0f };
		}
	}
	SetCameraPositionAndTarget_UpVecY(VGet(eye.x, eye.y, eye.z), VGet(plPos.x, plPos.y, plPos.z));//���_�A�����_��ݒ�
	FadeIn();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	pl->Draw();
	cube->Draw();
	if (CheckHandleASyncLoad(pl->GetPlayerHandle())){
		ld->Draw(SCREEN_SIZE_X - 70, SCREEN_SIZE_Y - 70);
	}
}

void GameplayingScene::FadeIn()
{
	if (alphaFlg != false){
		return;
	}
	if (alpha < 255){
		if (alphaFlg != true){
			alpha += 5;
		}
	}
}

void GameplayingScene::FadeOut()
{
	if (alphaFlg == false) {
		return;
	}
	if (alpha >= 0){
		alpha -= 5;
		if (alpha == 0) {
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			//Game::Instance().ChangeScene(new CountinueScene(key));
		}
	}
}

positin3D GameplayingScene::PlusVECTOR(positin3D pos, VECTOR vec) {
	positin3D tmpPos;
	tmpPos.x = pos.x + vec.x;
	tmpPos.y = pos.y + vec.y;
	tmpPos.z = pos.z + vec.z;
	return tmpPos;
}

void GameplayingScene::CameraRotation(float *x, float *y, const float ang, const float mx, const float my)
{
	const float ox = *x - mx, oy = *y - my;
	*x = ox * cos(ang) + oy * sin(ang);
	*y = -ox * sin(ang) + oy * cos(ang);
	*x += mx;
	*y += my;
}
