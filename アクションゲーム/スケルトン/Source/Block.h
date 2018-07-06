#pragma once
#include "CharactorObject.h"
#include <memory>

class Player;
class Camera;

//ÉuÉçÉbÉN
class Block :
	public CharactorObject
{
public:
	Block(std::weak_ptr<Player> _pl, std::weak_ptr<Camera> _cam, positin _pos);
	~Block();

	void Updata();
	void Draw();

private:
	std::weak_ptr<Player> pl;
};

