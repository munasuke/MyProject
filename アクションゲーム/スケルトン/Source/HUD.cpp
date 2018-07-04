#include "DxLib.h"
#include "Player.h"
#include "HUD.h"




HUD::HUD(std::weak_ptr<Player> pl) :
	_pl(pl), 
	_score(0),
	barTopH(LoadGraph("img/bar_top.png")),
	barBottomH(LoadGraph("img/bar_bottom.png")),
	heartH(LoadGraph("img/real_heart.png"))
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

	int life = _pl.lock()->GetLife();
	for (int i = 0; i < life; ++i) {
		DrawGraph(100 + i * 40, 100, heartH, true);//ƒ‰ƒCƒt•`‰æ
	}

}
