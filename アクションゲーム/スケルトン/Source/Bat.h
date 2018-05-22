#pragma once
#include "CharactorObject.h"
#include "Player.h"
#include <memory>
class Bat :
	public CharactorObject
{
public:
	Bat(std::weak_ptr<Player>pl);
	~Bat();
	void Updata();
	void Draw();
private:
	void NeutralUpdata();
	void FlyUpdata();
	void DieUpdata();
	void Damage();
	void IsHitPlayer();//playerとの当たり判定

	void(Bat::* _updata)();
	int speed;
	int _wait;//待機時間
	bool die;
	int _flySE;//羽音

	std::weak_ptr<Player>pl;
};

