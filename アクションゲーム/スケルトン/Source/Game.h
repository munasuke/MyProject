#pragma once
#include <memory>
#include "Player.h"

#define SCREEN_SIZE_X	768
#define SCREEN_SIZE_Y	448

class Game
{
public:
	~Game();
	static Game& Instance() {
		static Game instance;
		return instance;
	}
	void Init();//‰Šú‰»
	void Loop();//ƒ‹[ƒv
private:
	Game();
	Game(const Game&);
	std::shared_ptr<Player> pl;

	bool SysInit();

	int image[10];
};

