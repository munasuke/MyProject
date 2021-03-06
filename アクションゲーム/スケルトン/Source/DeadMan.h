#pragma once
#include "CharactorObject.h"
#include "Player.h"
#include <memory>

class Camera;

//class Player;
//敵
class DeadMan : public CharactorObject
{
public:
	DeadMan(std::weak_ptr<Player>pl, std::weak_ptr<Camera> cam, positin _pos);
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
	void IsHitPlayer();//playerとの当たり判定

	void(DeadMan::* _updata)();
	int _wait;//待機時間
	bool die;

	positin localPos;

	std::weak_ptr<Player>pl;
};

