#pragma once
#include "CharactorObject.h"
#include "Player.h"
#include <memory>
class Bat :
	public CharactorObject
{
public:
	Bat(std::weak_ptr<Player>pl, std::weak_ptr<Camera> cam, positin _pos);
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
	int _wait;//待機時間
	bool die;
	int _flySE;//羽音
	positin range;
	positin localPos;

	std::weak_ptr<Player>pl;
};

