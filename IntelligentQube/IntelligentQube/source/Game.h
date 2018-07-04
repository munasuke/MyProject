#pragma once
#include <memory>
#include "KeyInput.h"
#include "Scene/Scene.h"
#include "Typedef.h"

#define SCREEN_SIZE_X	1280
#define SCREEN_SIZE_Y	720


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

	Rect GetScreenSize();
private:
	//シングルトンのお決まり
	Game();//生成禁止
	Game(const Game&);//コピー禁止
	void operator=(const Game&) {};//代入禁止

	std::shared_ptr<KeyInput> k;
	std::shared_ptr<Scene> scene;

	bool SysInit();
	void Updata();
	int Draw();

	Rect screenSize;
};

