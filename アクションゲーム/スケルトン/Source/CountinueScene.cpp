#include "CountinueScene.h"
#include "Game.h"
#include "GameoverScene.h"
#include "DxLib.h"


CountinueScene::CountinueScene()
{
	for (int i = 0; i < 256; i++) {
		key[i] = 0;
		oldkey[i] = 0;
	}
	printf("Countinue Scene\n");
}


CountinueScene::~CountinueScene()
{
	printf("Countinue Scene is Deleted\n");
}

void CountinueScene::Updata()
{
	for (int i = 0; i < 256; i++) {
		oldkey[i] = key[i];
	}
	GetHitKeyStateAll(key);
	if ((key[KEY_INPUT_SPACE]&oldkey[KEY_INPUT_SPACE])^key[KEY_INPUT_SPACE]){
		Game::Instance().ChangeScene(new GameoverScene());
	}
}
