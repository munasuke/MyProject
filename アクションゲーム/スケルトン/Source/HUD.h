#pragma once
#include <memory>

class Player;

//画面上に表示される「UI」
class HUD
{
public:
	HUD(std::weak_ptr<Player> pl);
	~HUD();

	void Updata();
	void Draw(int sizey);
private:
	int barTopH;//上バーのUI画像ハンドル
	int barBottomH;//下バーのUI画像ハンドル
	int heartH;//ライフ画像ハンドル
	std::weak_ptr<Player> _pl;
	int _score;//スコア
};

