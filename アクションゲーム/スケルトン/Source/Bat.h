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
	void IsHitPlayer();//player‚Æ‚Ì“–‚½‚è”»’è

	void(Bat::* _updata)();
	int speed;
	int _wait;//‘Ò‹@ŽžŠÔ
	bool die;
	int _flySE;//‰H‰¹

	std::weak_ptr<Player>pl;
};

