#pragma once
#include "Scene.h"

class CountinueScene :
	public Scene
{
public:
	CountinueScene(std::weak_ptr<KeyInput> _key);
	~CountinueScene();
	void Updata();
	void Draw();
	void FadeIn();
	void FadeOut();
private:
	int cntImage;
};

