#include "GameplayingScene.h"
#include "Game.h"


GameplayingScene::GameplayingScene(std::weak_ptr<KeyInput> _key) : 
	_playerH(MV1LoadModel("models/Alicia/Alicia_solid.pmx")),
	_pos(VGet(0.0f, 0.0f, 0.0f)),
	_rot(VGet(0.0f, 0.0f, 0.0f))
{
	key = _key;
	alpha = 0;
	alphaFlg = false;

	//カメラの設定
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 15.0f, -25.0f), VGet(0.0f, 10.0f, 0.0f));//視点、注視点を設定
	SetupCamera_Perspective(RAD(60.0f));//遠近法カメラの設定
	SetCameraNearFar(0.5f, 300.0f);//クリップの設定

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

	if (key.lock()->IsPressing(PAD_INPUT_UP)){
		_pos.z++;
		_rot.y = RAD(180);
	}
	else if (key.lock()->IsPressing(PAD_INPUT_DOWN)){
		_pos.z--;
		_rot.y = RAD(0);
	}
	else if (key.lock()->IsPressing(PAD_INPUT_RIGHT)){
		_pos.x++;
		_rot.y = RAD(270);
	}
	else if (key.lock()->IsPressing(PAD_INPUT_LEFT)){
		_pos.x--;
		_rot.y = RAD(90);
	}
	FadeOut();
}

void GameplayingScene::Draw()
{
	FadeIn();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	if (_playerH == -1){
		printf("ロードされてないよ\n");
	}
	MV1SetPosition(_playerH, _pos);
	MV1SetRotationXYZ(_playerH, _rot);
	MV1DrawModel(_playerH);
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
