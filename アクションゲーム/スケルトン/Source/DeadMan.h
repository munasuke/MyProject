#pragma once
#include "CharactorObject.h"

class Player;
//“G
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
	void IsHitPlayer();//player‚Æ‚Ì“–‚½‚è”»’è

	void(DeadMan::* _updata)();
	Player* pl;
	int speed;
};

