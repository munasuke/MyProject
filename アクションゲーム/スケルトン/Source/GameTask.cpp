#include "GameTask.h"
#include "DxLib.h"

GameTask::GameTask()
{
	mode = GMODE_SYSINIT;
}


GameTask::~GameTask()
{
}

void GameTask::Updata(void)
{
}

void GameTask::Draw(void)
{
}

int GameTask::SysInit()
{
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText("1601296_宗岡春佳");
	if (DxLib_Init() == -1) return false;
	SetDrawScreen(DX_SCREEN_BACK);
	mode = GMODE_GAME;
}

int GameTask::GameInit()
{
	return true;
}

int GameTask::GameMain(void)
{
	GameUpdate();
	GameDraw();
	return true;
}

int GameTask::GameUpdate(void)
{
	return true;
}

int GameTask::GameDraw(void)
{
	ClsDrawScreen(); // 画面消去

	Draw();

	ScreenFlip();
	return true;
}

int GameTask::GameDestroy(void)
{
	DxLib_End();
	return true;
}
