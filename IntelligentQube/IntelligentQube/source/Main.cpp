#include "Main.h"
#include "Game.h"

int main()
{
	Game::Instance().Init();
	Game::Instance().Loop();
}