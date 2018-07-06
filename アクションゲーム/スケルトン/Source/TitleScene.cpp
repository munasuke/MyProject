#include "TitleScene.h"
#include "Game.h"
#include "GameplayingScene.h"
#include "DxLib.h"


TitleScene::TitleScene(std::weak_ptr<KeyInput> _key) : 
	titleImage(LoadGraph("img/title.png")), 
	pressImage(LoadGraph("img/pressstart.png")), 
	aflg(true),
	pressalpha(0),
	startSE(LoadSoundMem("se/start.mp3"))
{
	key = _key;
	alpha = 0;
	alphaFlg = false;
	printf("Title Scene\n");
}


TitleScene::~TitleScene()
{
	printf("Title Scene is Deleted\n\n");
}

void TitleScene::Updata()
{
	if (key.lock()->IsTrigger(PAD_INPUT_8)) {
		alphaFlg = true;
		PlaySoundMem(startSE, DX_PLAYTYPE_BACK);
	}
	FadeOut();
}

void TitleScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(0, 0, titleImage, true);
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
	FadeIn();
}

void TitleScene::FadeIn()
{
	if (alpha < 255) {
		if (alphaFlg != true) {
			alpha++;
		}
	}
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
