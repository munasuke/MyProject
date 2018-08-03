#pragma once
#include "Scene/Scene.h"
#include <memory>

class ModelLoader;
class Player;

class TitleScene :
	public Scene
{
public:
	TitleScene(std::weak_ptr<KeyInput> _key);
	~TitleScene();
	void Updata();
	void Draw();
	void FadeIn();
	void FadeOut();
private:
	int titleImage;
	int pressImage;
	bool aflg;
	int pressalpha;
	positin pos;

	std::shared_ptr<ModelLoader> loader;
	std::shared_ptr<Player> pl;
};

