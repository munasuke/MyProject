#include "Ground.h"



Ground::Ground(std::weak_ptr<Player>pl) :
	pl(pl),
	ground_line(340)
{
}


Ground::~Ground()
{
}

int Ground::GetCurrentGround() const
{
	
	return ground_line;
}
