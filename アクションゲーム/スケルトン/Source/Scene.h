#pragma once
#include "KeyInput.h"
#include <memory>

class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void Updata() = 0;//sceneXV—p
	virtual void Draw() = 0;
protected:
	std::weak_ptr<KeyInput> key;
	int bgm;
	int alpha;
};

