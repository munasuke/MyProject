#include "GameplayingScene.h"
#include "Game.h"
#include "NowLoading.h"
#include "Player.h"
#include "Game/Cube.h"


GameplayingScene::GameplayingScene(std::weak_ptr<KeyInput> _key)
{
	key = _key;
	alpha = 0;
	alphaFlg = false;

	ld = std::make_shared<NowLoading>();
	pl = std::make_shared<Player>(key);
	cube = std::make_shared<Cube>();

	//�J�����̐ݒ�
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 15.0f, -25.0f), VGet(0.0f, 10.0f, 0.0f));//���_�A�����_��ݒ�
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

	if (key.lock()->IsTrigger(PAD_INPUT_8)){
		alphaFlg = true;
	}
	pl->Updata();
	cube->Updata();

	FadeOut();
}

void GameplayingScene::Draw()
{
	FadeIn();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	pl->Draw();
	cube->Draw();
	if (CheckHandleASyncLoad(pl->GetPlayerHandle())){
		ld->Draw(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2);
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
