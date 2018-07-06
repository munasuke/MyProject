#include "Block.h"
#include "Player.h"
#include "Camera.h"


Block::Block(std::weak_ptr<Player> _pl, std::weak_ptr<Camera> _cam, positin _pos) :
	pl(_pl)
{
	camera = _cam;
	pos = _pos;
}


Block::~Block()
{
}

void Block::Updata()
{
}

void Block::Draw()
{
}
