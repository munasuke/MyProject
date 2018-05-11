#include "DxLib.h"
//#include "GameTask.h"
#include "Main.h"
#include "Init.h"
using namespace DxLib;

int image[10];

int LoadImage(void);
int Update(void);
int Draw(void);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SystemInit();
	LoadImage();
	pl = std::make_shared<Player>();
	//GameTask::Create();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Update();
		Draw();
		//GameTask::GetInstance()->Updata();
	}
	//GameTask::Destroy();
	DxLib_End();
	return 0;
}

int LoadImage() {
	image[0] = LoadGraph("img/splatterhouse.png");
	image[1] = LoadGraph("img/bar_top.png");
	image[2] = LoadGraph("img/bar_bottom.png");
	
	return true;
}

int Update() {
	pl->Update();
	return true;
}

int Draw() {
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
	return true;
}
