#pragma once
#include<memory>

class Player;

class Ground
{
public:
	Ground(std::weak_ptr<Player>pl);
	~Ground();
	int GetCurrentGround()const;//地面の高さを返す
private:
	std::weak_ptr<Player>pl;
	int ground_line;
};

