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
	void Fly();
	void Damage();
	void IsHitPlayer();

	void(Bat::* _updata)();
	int _wait;//‘Ò‹@ŽžŠÔ
	bool die;
	int _flySE;//‰H‰¹
	positin range;

	std::weak_ptr<Player>pl;
};

