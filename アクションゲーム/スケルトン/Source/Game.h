#pragma once
#include <memory>
#include "KeyInput.h"
#include "Scene.h"

#define SCREEN_SIZE_X	768
#define SCREEN_SIZE_Y	448


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
	std::shared_ptr<KeyInput> k;
	std::shared_ptr<Scene> scene;

	bool SysInit();
	void Updata();
	int Draw();
};

