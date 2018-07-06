#pragma once
#include "Scene.h"

const positin count = { 5, 2 };
const positin count_size = { 117, 159 };
const int count_max = 10;

const int time = 90;

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
	int flame;
	bool fadeFlag;
	Scene *scene;
};

