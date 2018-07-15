#include "GameplayingScene.h"
#include "Game.h"
#include "NowLoading.h"
#include "Player.h"
#include "Game/Cube.h"


GameplayingScene::GameplayingScene(std::weak_ptr<KeyInput> _key) : 
	camPos(VGet(0.0f, 15.0f, -25.0f)),
	targetPos(VGet(0.0f, 10.0f, 0.0f))
{
	key = _key;
	alpha = 0;
	alphaFlg = false;

	ld = std::make_shared<NowLoading>();
	pl = std::make_shared<Player>(key);
	cube = std::make_shared<Cube>();

	//カメラの設定
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
	if (CheckHitKey(KEY_INPUT_LSHIFT)) {
		if (key.lock()->IsTrigger(PAD_INPUT_1)) {
			//CameraRotation(camPos, targetPos, +Angle);
			CameraRotation(&camPos.x, &camPos.z, +90.0f * DX_PI_F / 180.0f, targetPos.x, targetPos.z);
		}
		else if (key.lock()->IsTrigger(PAD_INPUT_2)) {
			//CameraRotation(camPos, targetPos, -Angle);
			CameraRotation(&camPos.x, &camPos.z, -90.0f * DX_PI_F / 180.0f, targetPos.x, targetPos.z);
		}
	}
	else {
		if (key.lock()->IsPressing(PAD_INPUT_1)) {
			//CameraRotation(camPos, targetPos, +Angle);
			CameraRotation(&camPos.x, &camPos.z, +Angle, targetPos.x, targetPos.z);
		}
		if (key.lock()->IsPressing(PAD_INPUT_2)) {
			//CameraRotation(camPos, targetPos, -Angle);
			CameraRotation(&camPos.x, &camPos.z, -Angle, targetPos.x, targetPos.z);
		}
	}
	SetCameraPositionAndTarget_UpVecY(camPos, targetPos);//視点、注視点を設定
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

void GameplayingScene::CameraRotation(float *x, float *y, const float ang, const float mx, const float my)
{
	const float ox = *x - mx, oy = *y - my;
	*x = ox * cos(ang) + oy * sin(ang);
	*y = -ox * sin(ang) + oy * cos(ang);
	*x += mx;
	*y += my;
}
