#include "DxLib.h"
#include "Game.h"
#include "TitleScene.h"
#include "EnemyManager.h"
#include "Background.h"
#include "HUD.h"

//‰Šú‰»
void Game::Init()
{
	SysInit();
	pl = std::make_shared<Player>();
	ChangeScene(new TitleScene());
	EnemyManager::Create();
	EnemyManager::GetInstance()->Summons("DeadMan", pl, { 400, 340 });//“G¶¬
	EnemyManager::GetInstance()->Summons("DeadMan", pl, { 200, 340 });
	EnemyManager::GetInstance()->Summons("Bat", pl, { 700, 130 });
	EnemyManager::GetInstance()->Summons("Bat", pl, { 500, 130 });
	bg = new Background();
	hud = new HUD(*pl);
	bgm = LoadSoundMem("bgm/bgm1.mp3");
}

//ƒ‹[ƒv
void Game::Loop()
{
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();
		scene->Updata();
		pl->Updata();
		EnemyManager::GetInstance()->Updata();
		Draw();

		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		ScreenFlip();

	}
}

void Game::ChangeScene(Scene * _scene)
{
	scene.reset(_scene);
}

Game::Game()
{
}

Game::Game(const Game &)
{
}

bool Game::SysInit()
{
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText("1601296_@‰ªt‰À");
	if (DxLib_Init() == -1) {
		return false; 
	}
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

int Game::Draw()
{
	bg->Draw(SCREEN_SIZE_X);
	pl->Draw();
	EnemyManager::GetInstance()->Draw();
	hud->Draw(SCREEN_SIZE_Y);

	return true;
}

Game::~Game()
{
	EnemyManager::Destroy();
	delete bg;
	delete hud;
}
