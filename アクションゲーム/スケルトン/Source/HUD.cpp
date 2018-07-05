#include "DxLib.h"
#include "Player.h"
#include "HUD.h"




HUD::HUD(std::weak_ptr<Player> pl) :
	_pl(pl), 
	_score(0),
	barTopH(LoadGraph("img/bar_top.png")),
	barBottomH(LoadGraph("img/bar_bottom.png")),
	heartH(LoadGraph("img/real_heart_s.png")),
	_heartSize(5.0)
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
		DrawRotaGraph2(220 + i * 30, 400, 0, 0, _heartSize, 0.0, heartH, true);//ƒ‰ƒCƒt•`‰æ
	}
}
