#include "KeyInput.h"
#include "DxLib.h"



KeyInput::KeyInput()
{
	keyState = 0;
	keyStateOld = 0;
}


KeyInput::~KeyInput()
{
}

void KeyInput::Updata()
{
	keyStateOld = keyState;
	keyState = GetJoypadInputState(DX_INPUT_KEY_PAD1);//key‚Æpad
}

bool KeyInput::IsPressing(int id) const
{
	return keyState & id;
}

bool KeyInput::IsTrigger(int id) const
{
	return (keyState & id) && !(keyStateOld & id);
}
