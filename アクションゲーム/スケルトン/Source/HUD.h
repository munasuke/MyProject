#pragma once

//画面上に表示される「UI」
class HUD
{
public:
	HUD(const Player& pl);
	~HUD();

	void Updata();
	void Draw(int sizey);
private:
	int barTopH;//上バーのUI画像ハンドル
	int barBottomH;//下バーのUI画像ハンドル
	const Player& _pl;//playerへの参照
	int _score;//スコア
};

