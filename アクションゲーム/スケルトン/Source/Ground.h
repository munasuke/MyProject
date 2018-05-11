#pragma once
#include<memory>

class Player;

class Ground
{
public:
	Ground(std::weak_ptr<Player>pl);
	~Ground();
	int GetCurrentGround()const;//’n–Ê‚Ì‚‚³‚ğ•Ô‚·
private:
	std::weak_ptr<Player>pl;
	int ground_line;
};

