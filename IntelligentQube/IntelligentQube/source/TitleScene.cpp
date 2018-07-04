#include "Typedef.h"
#include "TitleScene.h"
#include "Game.h"
#include "GameplayingScene.h"
#include "DxLib.h"


TitleScene::TitleScene(std::weak_ptr<KeyInput> _key) : 
	titleImage(LoadGraph("img/iq.png")), 
	//pressImage(LoadGraph("img/pressstart.png")), 
	aflg(true),
	pressalpha(0)
	//startSE(LoadSoundMem("se/start.mp3"))
{
	key = _key;
	alpha = 0;
	alphaFlg = false;
	//printf("Title Scene\n");
	pos.x = 1280 / 2;
	pos.y = 720 / 2;
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetCameraNearFar(0.1f, 1000.0f);
}


TitleScene::~TitleScene()
{
	//printf("Title Scene is Deleted\n\n");
}

void TitleScene::Updata()
{
	if (key.lock()->IsTrigger(PAD_INPUT_8)) {
		alphaFlg = true;
		PlaySoundMem(startSE, DX_PLAYTYPE_BACK);
	}
	if (key.lock()->IsPressing(PAD_INPUT_UP)){
		pos.y += 2;
	}
	if (key.lock()->IsPressing(PAD_INPUT_DOWN)){
		pos.y -= 2;
	}
	if (key.lock()->IsPressing(PAD_INPUT_RIGHT)){
		pos.x += 2;
	}
	if (key.lock()->IsPressing(PAD_INPUT_LEFT)){
		pos.x -= 2;
	}
	
	FadeOut();
}

void TitleScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(0, 0, 1280, 720, titleImage, true);
	DrawSphere3D(VGet(pos.x, pos.y, 0.0f), 100.0f, 32, GetColor(255, 255, 128), GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, pressalpha);
	DrawGraph(SCREEN_SIZE_X/2 - 356/2, SCREEN_SIZE_Y - 100, pressImage, true);
	if (aflg == true && alphaFlg == false){
		if (pressalpha < 256){
			pressalpha += 4;
		}
		else{
			aflg = false;
		}
	}
	else{
		if(pressalpha > 0){
			pressalpha -= 4;
		}
		else{
			aflg = true;
		}
	}
	if (alpha < 255){
		if (alphaFlg != true){
			alpha++;
		}
	}
}

void TitleScene::FadeIn()
{
}

void TitleScene::FadeOut()
{
	if (alphaFlg == false) {
		return;
	}
	if (alpha >= 0){
		pressalpha--;
		alpha--;
		if (alpha == 0) {
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			Game::Instance().ChangeScene(new GameplayingScene(key));
		}
	}
}
