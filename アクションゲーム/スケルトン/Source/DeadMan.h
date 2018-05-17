#pragma once
#include "CharactorObject.h"

class Player;
//“G
class DeadMan : CharactorObject
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

	void(DeadMan::* _updata)();
	Player* pl;
	int speed;
};

