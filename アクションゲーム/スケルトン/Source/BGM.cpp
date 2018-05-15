#include "DxLib.h"
#include "BGM.h"


BGM::BGM() : 
	bgm(LoadSoundMem("bgm/bgm1.mp3"))
{
}

BGM::~BGM()
{
}
