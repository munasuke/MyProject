#include "DxLib.h"
#include "Background.h"

Background::Background()
{
	bgH = LoadGraph("img/splatterhouse.png");
}

Background::~Background()
{
}

void Background::Updata()
{
	//�����Ŕw�i����������Ƃ��邩��
}

void Background::Draw(const int sizex)
{
	DrawGraph(0, 0, bgH, true);
	DrawTurnGraph(576, 0, bgH, true);

#ifdef _DEBUG
	DrawLine(0, 340, sizex, 340, 0x00ff00);
#endif
}
