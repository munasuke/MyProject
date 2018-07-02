#pragma once
#include "Scene.h"
#include "Player.h"
#include <memory>

class Background;
class HUD;
class Camera;
class Stage;

class GameplayingScene :
	public Scene
{
public:
	GameplayingScene(std::weak_ptr<KeyInput> _key);
	~GameplayingScene();
	void Updata();
	void Draw();
	void FadeIn();
	void FadeOut();
private:
	std::shared_ptr<Stage> st;
	std::shared_ptr<Player> pl;
	Background* bg;//îwåi
	HUD* hud;//UI
	std::shared_ptr<Camera> camera;
};

