#pragma once
#include <memory>
#include "Player.h"
#include "Scene.h"

#define SCREEN_SIZE_X	768
#define SCREEN_SIZE_Y	448

class Background;
class HUD;

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
	void ChangeScene(Scene* _scene);
private:
	Game();
	Game(const Game&);
	std::shared_ptr<Scene> scene;
	std::shared_ptr<Player> pl;
	Background* bg;//�w�i
	HUD* hud;//UI
	int bgm;

	bool SysInit();
	int Draw();
};

