#pragma once
#include <memory>
#include "Player.h"
#include "Scene.h"

#define SCREEN_SIZE_X	768
#define SCREEN_SIZE_Y	448

class Background;
class HUD;

//アプリ管理クラス
class Game
{
public:
	~Game();
	static Game& Instance() {
		static Game instance;
		return instance;
	}
	void Init();//初期化
	void Loop();//ループ
	void ChangeScene(Scene* _scene);
private:
	Game();
	Game(const Game&);
	std::shared_ptr<Scene> scene;
	std::shared_ptr<Player> pl;
	Background* bg;//背景
	HUD* hud;//UI
	int bgm;

	bool SysInit();
	int Draw();
};

