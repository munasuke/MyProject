#pragma once
#include "CharactorObject.h"

class Player;
//�G
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
	void IsHitPlayer();//player�Ƃ̓����蔻��

	void(DeadMan::* _updata)();
	Player* pl;
	int speed;
};

