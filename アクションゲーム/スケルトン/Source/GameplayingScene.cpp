#include "GameplayingScene.h"
#include "Game.h"
#include "EnemyManager.h"
#include "Background.h"
#include "HUD.h"
#include "CountinueScene.h"
#include "DxLib.h"


GameplayingScene::GameplayingScene(std::weak_ptr<KeyInput> _key)
{
	key = _key;
	pl = std::make_shared<Player>(key);
	EnemyManager::Create();
	EnemyManager::GetInstance()->Summons("DeadMan", pl, { 400, 340 });//“G¶¬
	EnemyManager::GetInstance()->Summons("DeadMan", pl, { 200, 340 });
	EnemyManager::GetInstance()->Summons("Bat", pl, { 700, 130 });
	EnemyManager::GetInstance()->Summons("Bat", pl, { 500, 130 });
	bg = new Background();
	hud = new HUD(*pl);
	bgm = LoadSoundMem("bgm/bgm1.mp3");

	printf("Gameplaying Scene\n");
}


GameplayingScene::~GameplayingScene()
{
	EnemyManager::Destroy();
	delete bg;
	delete hud;

	printf("Gameplaying Scene is Deleted\n\n");
}

void GameplayingScene::Updata()
{
	pl->Updata();
	EnemyManager::GetInstance()->Updata();
	if (key.lock()->IsTrigger(PAD_INPUT_8)){
		Game::Instance().ChangeScene(new CountinueScene(key));
	}
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}

void GameplayingScene::Draw()
{
	bg->Draw(SCREEN_SIZE_X);
	pl->Draw();
	EnemyManager::GetInstance()->Draw();
	hud->Draw(SCREEN_SIZE_Y);
}
