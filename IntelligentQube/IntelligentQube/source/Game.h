#pragma once
#include <memory>
#include "KeyInput.h"
#include "Scene/Scene.h"
#include "Typedef.h"

#define SCREEN_SIZE_X	1280
#define SCREEN_SIZE_Y	720


//�A�v���Ǘ��N���X
class Game
{
public:
	~Game();
	static Game& Instance() {
		static Game instance;
		return instance;
	}

	void Init();//������
	void Loop();//���[�v
	void ChangeScene(Scene* _scene);

	Rect GetScreenSize();
private:
	//�V���O���g���̂����܂�
	Game();//�����֎~
	Game(const Game&);//�R�s�[�֎~
	void operator=(const Game&) {};//����֎~

	std::shared_ptr<KeyInput> k;
	std::shared_ptr<Scene> scene;

	bool SysInit();
	void Updata();
	int Draw();

	Rect screenSize;
};

