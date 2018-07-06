#include "GameoverScene.h"
#include "Game.h"
#include "TitleScene.h"
#include "DxLib.h"



GameoverScene::GameoverScene(std::weak_ptr<KeyInput> _key) : overImage(LoadGraph("img/gameover.png"))
{
	key = _key;
	alpha = 0;
	alphaFlg = false;
	printf("Gameover Scene\n");
}


GameoverScene::~GameoverScene()
{
	printf("Gameover Scene is Deleted\n\n");
}

void GameoverScene::Updata()
{
	if (key.lock()->IsTrigger(PAD_INPUT_8)){
		alphaFlg = true;
	}
	FadeOut();
}

void GameoverScene::Draw()
{
	FadeIn();
	DrawGraph(0, 0, overImage, true);
}

void GameoverScene::FadeIn()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	if (!alphaFlg) {
		if (alpha < 256) {
			alpha+=10;
		}
	}
}

void GameoverScene::FadeOut()
{
	if (!alphaFlg) {
		return;
	}
	if (alpha >= 0) {
		alpha-=10;
		if (alpha == 0) {
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			Game::Instance().ChangeScene(new TitleScene(key));
		}
	}
}
