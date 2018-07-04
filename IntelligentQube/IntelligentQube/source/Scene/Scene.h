#pragma once
#include "../KeyInput.h"
#include <memory>

class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void Updata() = 0;//sceneçXêVóp
	virtual void Draw() = 0;
	virtual void FadeIn() = 0;
	virtual void FadeOut() = 0;
protected:
	std::weak_ptr<KeyInput> key;
	int bgm;
	int alpha;
	bool alphaFlg;
};

