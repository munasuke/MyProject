#pragma once

#define KEY(X) (key[X]&oldkey[X])^key[X]

class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void Updata() = 0;//sceneXV—p

protected:
	char key[256];
	char oldkey[256];
};

