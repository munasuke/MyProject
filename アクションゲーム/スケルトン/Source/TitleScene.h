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
private:
	int titleImage;
	int pressImage;
	bool aflg;
	int pressalpha;
	bool flg;
};

