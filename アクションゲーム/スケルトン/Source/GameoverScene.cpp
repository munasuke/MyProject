#include "GameoverScene.h"
#include "Game.h"
#include "TitleScene.h"
#include "DxLib.h"



GameoverScene::GameoverScene()
{
	for (int i = 0; i < 256; i++) {
		key[i] = 0;
		oldkey[i] = 0;
	}
	printf("Gameover Scene\n");
}


GameoverScene::~GameoverScene()
{
	printf("Gameover Scene is Deleted\n");
}

void GameoverScene::Updata()
{
	for (int i = 0; i < 256; i++) {
		oldkey[i] = key[i];
	}
	GetHitKeyStateAll(key);
	if ((key[KEY_INPUT_SPACE]&oldkey[KEY_INPUT_SPACE])^key[KEY_INPUT_SPACE]){
		Game::Instance().ChangeScene(new TitleScene());
	}
}
