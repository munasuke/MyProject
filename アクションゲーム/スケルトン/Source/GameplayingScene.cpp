#include "GameplayingScene.h"
#include "Game.h"
#include "Stage.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "EventManager.h"
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
	EventManager::Create();
	bg = new Background(camera);
	hud = new HUD(pl);
	bgm = LoadSoundMem("bgm/bgm1.mp3");
	x = 2;
	eventx = 2;

	printf("Gameplaying Scene\n");
}


GameplayingScene::~GameplayingScene()
{
	EnemyManager::Destroy();
	EventManager::Destroy();
	delete bg;
	delete hud;

	printf("Gameplaying Scene is Deleted\n\n");
}

void GameplayingScene::Updata()
{
	camera->Update();
	bg->Updata();
	pl->Updata();
	positin tmp;
	y = 0;
	//敵データの数だけ描画する
	for (auto& em : st->GetEnemyData((int)camera->GetPosition().x, (int)(camera->GetPosition().x + SCREEN_SIZE_X / 2 + CHIP_SIZE * 3))) {
		if (em == 1) {
			tmp = { x * CHIP_SIZE, y * CHIP_SIZE - 110 };
			EnemyManager::GetInstance()->Summons("DeadMan", pl, camera, tmp);
		}
		else if (em == 2) {
			tmp = { x * CHIP_SIZE, y * CHIP_SIZE };
			EnemyManager::GetInstance()->Summons("Bat", pl, camera, tmp);
		}
		else if (em == 3) {
			tmp = { x * CHIP_SIZE, y * CHIP_SIZE - 100};
			EnemyManager::GetInstance()->Summons("Pike", pl, camera, tmp);
		}
		++y;
		if (y >= st->GetStageRange().Height() / CHIP_SIZE) {
			++x;
			y = 0;
		}
	}

	//イベントデータの数だけ描画
	for (auto& ev : st->GetEventData((int)camera->GetPosition().x, (int)(camera->GetPosition().x + SCREEN_SIZE_X / 2 + CHIP_SIZE * 3))) {
		if (ev == 1) {
			tmp = { eventx * CHIP_SIZE, y * CHIP_SIZE - 460 };
			EventManager::GetInstance()->CallEventObject("Ladder", pl, camera, tmp);
		}
		++y;
		if (y >= st->GetStageRange().Height() / CHIP_SIZE) {
			++eventx;
			y = 0;
		}
	}

	if (pl->GetDieFlag()){
		alphaFlg = true;
	}
	
	EnemyManager::GetInstance()->Updata();
	EventManager::GetInstance()->Updata();
	if (key.lock()->IsTrigger(PAD_INPUT_8)){
		alphaFlg = true;
	}
	FadeOut();
	DxLib::PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}

void GameplayingScene::Draw()
{
	FadeIn();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	bg->Draw(SCREEN_SIZE_X);
	pl->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	EnemyManager::GetInstance()->Draw();
	EventManager::GetInstance()->Draw();
	hud->Draw(SCREEN_SIZE_Y);
}

void GameplayingScene::FadeIn()
{
	if (alphaFlg != false){
		return;
	}
	if (alpha < 255){
		if (alphaFlg != true){
			alpha += 10;
		}
	}
}

void GameplayingScene::FadeOut()
{
	if (alphaFlg == false) {
		return;
	}
	if (alpha >= 0){
		alpha -= 10;
		if (alpha == 0) {
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			Game::Instance().ChangeScene(new CountinueScene(key));
		}
	}
}
