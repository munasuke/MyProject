#include "GameplayingScene.h"
#include "Game.h"
#include "NowLoading.h"
#include "Player.h"
#include "Game/Cube.h"

GameplayingScene::GameplayingScene(std::weak_ptr<KeyInput> _key) : 
	camPos(0.0f, 30.0f, -35.0f),
	targetPos(0.0f, 10.0f, 0.0f),
	bgmH(LoadSoundMem("bgm/セルリアン.mp3"))
{
	key = _key;
	alpha = 0;
	alphaFlg = false;


	ld = std::make_shared<NowLoading>();
	//非同期読み込み
	SetUseASyncLoadFlag(true);

	SetTextureAddressModeUV(DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP);
	pl = std::make_shared<Player>(key);

	//キューブズ
	cb.resize(20);
	float z = 20.0f;
	std::map<std::string, COLOR_F> color = {
		{ "Normal", GetColorF(0.2f, 0.2f, 0.2f, 1.0f) },
		{ "Advanced", GetColorF(0.2f, 1.0f, 0.2f, 1.0f) },
		{ "Forbidden", GetColorF(0.0f, 0.0f, 0.0f, 1.0f) }
	};
	cb[0] = std::make_shared<Cube>(VGet(20.0f, 5.0f, z), VGet(1.0f, 1.0f, 1.0f), color["Normal"]);
	cb[1] = std::make_shared<Cube>(VGet(10.0f, 5.0f, z), VGet(1.0f, 1.0f, 1.0f), color["Normal"]);
	cb[2] = std::make_shared<Cube>(VGet(0.0f, 5.0f, z), VGet(1.0f, 1.0f, 1.0f), color["Advanced"]);
	cb[3] = std::make_shared<Cube>(VGet(-10.0f, 5.0f, z), VGet(1.0f, 1.0f, 1.0f), color["Normal"]);

	cb[4] = std::make_shared<Cube>(VGet(20.0f, 5.0f, z + 10.0f), VGet(1.0f, 1.0f, 1.0f), color["Advanced"]);
	cb[5] = std::make_shared<Cube>(VGet(10.0f, 5.0f, z + 10.0f), VGet(1.0f, 1.0f, 1.0f), color["Normal"]);
	cb[6] = std::make_shared<Cube>(VGet(0.0f, 5.0f, z + 10.0f), VGet(1.0f, 1.0f, 1.0f), color["Normal"]);
	cb[7] = std::make_shared<Cube>(VGet(-10.0f, 5.0f, z + 10.0f), VGet(1.0f, 1.0f, 1.0f), color["Forbidden"]);

	cb[8] = std::make_shared<Cube>(VGet(20.0f, 5.0f, z + 20.0f), VGet(1.0f, 1.0f, 1.0f), color["Normal"]);
	cb[9] = std::make_shared<Cube>(VGet(10.0f, 5.0f, z + 20.0f), VGet(1.0f, 1.0f, 1.0f), color["Forbidden"]);
	cb[10] = std::make_shared<Cube>(VGet(0.0f, 5.0f, z + 20.0f), VGet(1.0f, 1.0f, 1.0f), color["Normal"]);
	cb[11] = std::make_shared<Cube>(VGet(-10.0f, 5.0f, z + 20.0f), VGet(1.0f, 1.0f, 1.0f), color["Advanced"]);

	cb[12] = std::make_shared<Cube>(VGet(20.0f, 5.0f, z + 30.0f), VGet(1.0f, 1.0f, 1.0f), color["Normal"]);
	cb[13] = std::make_shared<Cube>(VGet(10.0f, 5.0f, z + 30.0f), VGet(1.0f, 1.0f, 1.0f), color["Advanced"]);
	cb[14] = std::make_shared<Cube>(VGet(0.0f, 5.0f, z + 30.0f), VGet(1.0f, 1.0f, 1.0f), color["Forbidden"]);
	cb[15] = std::make_shared<Cube>(VGet(-10.0f, 5.0f, z + 30.0f), VGet(1.0f, 1.0f, 1.0f), color["Advanced"]);

	cb[16] = std::make_shared<Cube>(VGet(20.0f, 5.0f, z + 40.0f), VGet(1.0f, 1.0f, 1.0f), color["Forbidden"]);
	cb[17] = std::make_shared<Cube>(VGet(10.0f, 5.0f, z + 40.0f), VGet(1.0f, 1.0f, 1.0f), color["Forbidden"]);
	cb[18] = std::make_shared<Cube>(VGet(0.0f, 5.0f, z + 40.0f), VGet(1.0f, 1.0f, 1.0f), color["Normal"]);
	cb[19] = std::make_shared<Cube>(VGet(-10.0f, 5.0f, z + 40.0f), VGet(1.0f, 1.0f, 1.0f), color["Forbidden"]);

	//床
	VECTOR scale = { 4.0f, 5.0f, 12.0f };
	groundCube = std::make_shared<Cube>(VGet(5.0f, -25.0f, 5.0f), scale, color["Normal"]);

	//視線ベクトル
	toEyeVector = VSub(VGet(camPos.x, camPos.y, camPos.z), VGet(targetPos.x, targetPos.y, targetPos.z));

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
	PlaySoundMem(bgmH, DX_PLAYTYPE_LOOP);
}


GameplayingScene::~GameplayingScene()
{
	printf("Gameplaying Scene is Deleted\n\n");
}

void GameplayingScene::Updata()
{
	if (CheckHandleASyncLoad(pl->GetPlayerHandle())) {
		return;
	}
	//キューブ操作
	pl->Updata();
	for (int i = 0; i < cb.size(); i++) {
		if (key.lock()->IsTrigger(PAD_INPUT_8)) {
			cb[i]->RollOver(0, 1);
		}
		if (key.lock()->IsTrigger(PAD_INPUT_5)) {
			cb[i]->RollOver(0, -1);
		}
		if (key.lock()->IsTrigger(PAD_INPUT_6)) {
			cb[i]->RollOver(1, 0);
		}
		if (key.lock()->IsTrigger(PAD_INPUT_4)) {
			cb[i]->RollOver(-1, 0);
		}
		cb[i]->Updata();
	}

	FadeOut();
}

void GameplayingScene::Draw()
{
	if (!CheckHandleASyncLoad(pl->GetPlayerHandle())) {
		auto plPos = pl->GetPosition();
		auto eye = VAdd(VGet(plPos.x, plPos.y, plPos.z), toEyeVector);//PlusVECTOR(plPos, toEyeVector);

		if (key.lock()->IsPressing(PAD_INPUT_1)) {
			CameraRotation(VGet(0.0f, 1.0f, 0.0f), toEyeVector);
		}
		else if (key.lock()->IsPressing(PAD_INPUT_2)) {
			CameraRotation(toEyeVector, VGet(0.0f, 1.0f, 0.0f));
		}

		SetCameraPositionAndTarget_UpVecY(VGet(eye.x, eye.y, eye.z), VGet(plPos.x, plPos.y, plPos.z));//視点、注視点を設定

		FadeIn();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		pl->Draw();
		for (int i = 0; i < cb.size(); i++) {
			cb[i]->Draw();
		}
		groundCube->Draw();
	}
	else {
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

void GameplayingScene::CameraRotation(VECTOR vec1, VECTOR vec2)
{
	//上ベクトルと視線ベクトルを外積
	VECTOR crossVec = VCross(vec1, vec2);
	//外積したベクトルを正規化して、視線ベクトルと加算
	VECTOR addVec = VAdd(toEyeVector, VNorm(crossVec));
	//加算したベクトルを正規化して、視線ベクトルのサイズをかけて長さを揃える
	toEyeVector = VScale(VNorm(addVec), VSize(toEyeVector));
}
