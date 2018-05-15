#include "DxLib.h"
#include "Player.h"
#include "HUD.h"




HUD::HUD(const Player& pl) : 
	_pl(pl), 
	_score(0),
	barTopH(LoadGraph("img/bar_top.png")),
	barBottomH(LoadGraph("img/bar_bottom.png"))
{
}


HUD::~HUD()
{
}

void HUD::Updata()
{
}

void HUD::Draw(int sizey)
{
	DrawGraph(0, 0, barTopH, true);
	DrawGraph(0, sizey - 64, barBottomH, true);
}
