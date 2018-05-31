#pragma once
#include "Scene.h"


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
	int startSE;
};

