#include "GameplayingScene.h"



GameplayingScene::GameplayingScene()
{
	for (int i = 0; i < 256; i++) {
		key[i] = 0;
		oldkey[i] = 0;
	}
	printf("Gameplaying Scene\n");
}


GameplayingScene::~GameplayingScene()
{
	printf("Gameplaying Scene is Deleted\n");
}

void GameplayingScene::Updata()
{
	for (int i = 0; i < 256; i++) {
		oldkey[i] = key[i];
	}
	GetHitKeyStateAll(key);
	if ((key[KEY_INPUT_SPACE]&oldkey[KEY_INPUT_SPACE])^key[KEY_INPUT_SPACE]){
		Game::Instance().ChangeScene(new CountinueScene());
	}
}
