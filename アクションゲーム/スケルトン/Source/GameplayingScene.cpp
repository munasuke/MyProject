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
	bg = new Background(camera);
	hud = new HUD(pl);
	bgm = LoadSoundMem("bgm/bgm1.mp3");
	x = 2;

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
	bg->Updata();
	pl->Updata();
	positin tmp;
	y = 0;
	//“Gƒf[ƒ^‚Ì”‚¾‚¯•`‰æ‚·‚é
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
		}
		++y;
		if (y >= st->GetStageRange().Height() / CHIP_SIZE) {
			++x;
			y = 0;
		}
	}

	if (pl->GetDieFlag()){
		alphaFlg = true;
	}
	
	EnemyManager::GetInstance()->Updata();
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
