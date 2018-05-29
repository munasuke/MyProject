#pragma once
#include "CharactorObject.h"
#include "Player.h"
#include <memory>

//class Player;
//�G
class DeadMan : public CharactorObject
{
public:
	DeadMan(std::weak_ptr<Player>pl, positin _pos);
	~DeadMan();
	void Updata();
	void Draw();
	bool GetDie();
private:
	void NeutralUpdata();
	void WalkUpdata();
	void DieUpdata();
	void DamageUpdata();
	void Damage();
	void IsHitPlayer();//player�Ƃ̓����蔻��

	void(DeadMan::* _updata)();
	int _wait;//�ҋ@����
	bool die;

	std::weak_ptr<Player>pl;
};

