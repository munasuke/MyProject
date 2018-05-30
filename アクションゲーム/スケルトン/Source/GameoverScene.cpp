#include "GameoverScene.h"
#include "Game.h"
#include "TitleScene.h"
#include "DxLib.h"



GameoverScene::GameoverScene(std::weak_ptr<KeyInput> _key) : overImage(LoadGraph("img/gameover.png"))
{
	key = _key;
	alpha = 0;
	printf("Gameover Scene\n");
}


GameoverScene::~GameoverScene()
{
	printf("Gameover Scene is Deleted\n\n");
}

void GameoverScene::Updata()
{
	if (key.lock()->IsTrigger(PAD_INPUT_8)){
		Game::Instance().ChangeScene(new TitleScene(key));
	}
}

void GameoverScene::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(0, 0, overImage, true);
	if (alpha < 256){
		alpha++;
	}
}
