#pragma once
#include<memory>

class Player;

class Ground
{
public:
	Ground(std::weak_ptr<Player>pl);
	~Ground();
	int GetCurrentGround()const;//�n�ʂ̍�����Ԃ�
private:
	std::weak_ptr<Player>pl;
	int ground_line;
};

