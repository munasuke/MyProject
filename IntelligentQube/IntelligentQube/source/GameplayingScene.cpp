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

	//カメラの設定
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 15.0f, -25.0f), VGet(0.0f, 10.0f, 0.0f));//視点、注視点を設定
	SetupCamera_Perspective(RAD(90.0f));//遠近法カメラの設定
	SetCameraNearFar(0.5f, 300.0f);//クリップの設定

	//ライトの設定
	SetLightEnable(true);
	SetUseLighting(true);
	//ライトの方向と属性の設定
	SetLightDirection(VGet(1.0f, 1.0f, 1.0f));//平行光線ベクトル
	SetLightDifColor(GetColorF(0.8f, 0.8f, 0.8f, 1.0f));//ディフューズ
	SetLightAmbColor(GetColorF(0.4f, 0.4f, 0.4f, 1.0f));//アンビエント
	SetLightSpcColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f));//スペキュラー

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
