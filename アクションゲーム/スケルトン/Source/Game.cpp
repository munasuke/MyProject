#include "DxLib.h"
#include "Game.h"

//‰Šú‰»
void Game::Init()
{
	SysInit();
	pl = std::make_shared<Player>();
	deadman = std::make_shared<DeadMan>();
	bg = std::make_shared<Background>();
	hud = std::make_shared<HUD>(*pl);
	bgm = LoadSoundMem("bgm/bgm1.mp3");
}

//ƒ‹[ƒv
void Game::Loop()
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		pl->Updata();
		Draw();
	}
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
	if (DxLib_Init() == -1) return false;
	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

int Game::Draw()
{
	ClsDrawScreen();

	bg->Draw(SCREEN_SIZE_X);
	pl->Draw();
	deadman->Draw();
	hud->Draw(SCREEN_SIZE_Y);

	ScreenFlip();
	return true;
}


Game::~Game()
{
}
