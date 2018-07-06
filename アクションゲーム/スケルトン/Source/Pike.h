#pragma once
#include "CharactorObject.h"
#include <memory>

class Player;
class Camera;

//çY
class Pike :
	public CharactorObject
{
public:
	Pike(std::weak_ptr<Player> _pl, std::weak_ptr<Camera> _cam, positin _pos);
	~Pike();

	void Updata();
	void Draw();

	void IsHitPlayer();
private:
	std::weak_ptr<Player> pl;
	std::weak_ptr<Camera> cam;
	positin localPos;
};

