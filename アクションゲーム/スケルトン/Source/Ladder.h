#pragma once
#include "CharactorObject.h"
#include<memory>

class Player;
class Camera;

class Ladder :
	public CharactorObject
{
public:
	Ladder(std::weak_ptr<Player> _pl, std::weak_ptr<Camera> _cam, positin _pos);
	~Ladder();

	void Updata();
	void Draw();
private:
	std::weak_ptr<Player> pl;
	positin localPos;
};

