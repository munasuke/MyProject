#include "def.h"
#include "Init.h"
#include "DxLib.h"

bool SystemInit(void) {
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText("1601296_è@â™ètâ¿");
	if (DxLib_Init() == -1) return false;
	SetDrawScreen(DX_SCREEN_BACK);
}