#include "TitleScene.h"
#include "Game.h"
#include "GameplayingScene.h"
#include "DxLib.h"


TitleScene::TitleScene()
{
	for (int i = 0; i < 256; i++) {
		key[i] = 0;
		oldkey[i] = 0;
	}
	printf("Title Scene\n");
}


TitleScene::~TitleScene()
{
	printf("Title Scene is Deleted\n");
}

void TitleScene::Updata()
{
	for (int i = 0; i < 256; i++) {
		oldkey[i] = key[i];
	}
	GetHitKeyStateAll(key);
	if ((key[KEY_INPUT_SPACE]&oldkey[KEY_INPUT_SPACE])^key[KEY_INPUT_SPACE]){
		Game::Instance().ChangeScene(new GameplayingScene());
	}
}
