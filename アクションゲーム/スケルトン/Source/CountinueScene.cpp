#include "CountinueScene.h"
#include "Game.h"
#include "GameoverScene.h"
#include "DxLib.h"


CountinueScene::CountinueScene(std::weak_ptr<KeyInput> _key)
{
	key = _key;
	printf("Countinue Scene\n");
}


CountinueScene::~CountinueScene()
{
	printf("Countinue Scene is Deleted\n\n");
}

void CountinueScene::Updata()
{
	if (key.lock()->IsTrigger(PAD_INPUT_8)){
		Game::Instance().ChangeScene(new GameoverScene(key));
	}
}

void CountinueScene::Draw()
{
}
