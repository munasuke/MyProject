#include "GameplayingScene.h"
#include "Game.h"
#include "Stage.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "Background.h"
#include "HUD.h"
#include "CountinueScene.h"
#include "DxLib.h"


GameplayingScene::GameplayingScene(std::weak_ptr<KeyInput> _key)
{
	key = _key;
	alpha = 0;
	alphaFlg = false;

	st = std::make_shared<Stage>();
	camera = std::make_shared<Camera>(st);
	pl = std::make_shared<Player>(key, camera);
	camera->SetFocus(pl);
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
	camera->Update();
	pl->Updata();
	EnemyManager::GetInstance()->Updata();
	if (key.lock()->IsTrigger(PAD_INPUT_8)){
		alphaFlg = true;
	}
	FadeOut();
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}

void GameplayingScene::Draw()
{
	FadeIn();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	bg->Draw(SCREEN_SIZE_X);
	pl->Draw();
	EnemyManager::GetInstance()->Draw();
	hud->Draw(SCREEN_SIZE_Y);
}

void GameplayingScene::FadeIn()
{
	if (alphaFlg != false){
		return;
	}
	if (alpha < 255){
		if (alphaFlg != true){
			alpha += 5;
		}
	}
}

void GameplayingScene::FadeOut()
{
	if (alphaFlg == false) {
		return;
	}
	if (alpha >= 0){
		alpha -= 5;
		if (alpha == 0) {
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			Game::Instance().ChangeScene(new CountinueScene(key));
		}
	}
}
