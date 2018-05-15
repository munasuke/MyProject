#pragma once
#include <memory>
#include "Player.h"
#include "Background.h"
#include "HUD.h"

#define SCREEN_SIZE_X	768
#define SCREEN_SIZE_Y	448


//�A�v���Ǘ��N���X
class Game
{
public:
	~Game();
	static Game& Instance() {
		static Game instance;
		return instance;
	}
	void Init();//������
	void Loop();//���[�v
private:
	Game();
	Game(const Game&);
	std::shared_ptr<Player> pl;
	std::shared_ptr<Background> bg;
	std::shared_ptr<HUD> hud;
	int bgm;

	bool SysInit();
	int Draw();
};

