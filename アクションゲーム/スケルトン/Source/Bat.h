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
	void IsHitPlayer();//player�Ƃ̓����蔻��

	void(Bat::* _updata)();
	int speed;
	int _wait;//�ҋ@����
	bool die;
	int _flySE;//�H��

	std::weak_ptr<Player>pl;
};

