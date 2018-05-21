#pragma once
#include "CharactorObject.h"

class Player;
//敵
class DeadMan : public CharactorObject
{
public:
	DeadMan();
	~DeadMan();
	void Updata();
	void Draw();
private:
	void NeutralUpdata();
	void WalkUpdata();
	void DieUpdata();
	void Damage();
	void IsHitPlayer();//playerとの当たり判定

	void(DeadMan::* _updata)();
	Player* pl;
	int speed;
};

