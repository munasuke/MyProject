#include "def.h"
#include "Game.h"
#include "DxLib.h"


void Game::Init()
{
	SysInit();
	//backGroundÇ…à⁄Ç∑
	image[0] = LoadGraph("img/splatterhouse.png");
	image[1] = LoadGraph("img/bar_top.png");
	image[2] = LoadGraph("img/bar_bottom.png");
}

void Game::Loop()
{
	pl->Updata();
	//backGroundÇ…à⁄Ç∑
	ClsDrawScreen();

	DrawGraph(0, 0, image[0], true);
	DrawTurnGraph(576, 0, image[0], true);
	DrawGraph(0, 0, image[1], true);
	DrawGraph(0, SCREEN_SIZE_Y - 64, image[2], true);
	pl->Draw();

	DrawLine(0, 340, SCREEN_SIZE_X, 340, 0x00ff00);

	DrawFormatString(0, 0, 0xff0000, "%d, %d", pl->GetPos());
	DrawFormatString(0, 30, 0xff0000, "%d, %d", pl->GetVec());

	ScreenFlip();
}

Game::Game()
{
	pl = std::make_shared<Player>();
}

Game::Game(const Game &)
{
}


bool Game::SysInit()
{
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText("1601296_è@â™ètâ¿");
	if (DxLib_Init() == -1) return false;
	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}


Game::~Game()
{
}
