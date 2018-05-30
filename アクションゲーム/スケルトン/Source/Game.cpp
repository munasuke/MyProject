#include "DxLib.h"
#include "Game.h"
#include "TitleScene.h"

//������
void Game::Init()
{
	SysInit();
	k = std::make_shared<KeyInput>();
	ChangeScene(new TitleScene(k));
}

//���[�v
void Game::Loop()
{
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();

		Updata();
		Draw();

		ScreenFlip();

	}
}

void Game::ChangeScene(Scene * _scene)
{
	scene.reset(_scene);
}

Game::Game()
{
}

Game::Game(const Game &)
{
}

bool Game::SysInit()
{
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	SetWindowText("1601296_�@���t��");
	if (DxLib_Init() == -1) {
		return false; 
	}
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

void Game::Updata()
{
		k->Updata();
		scene->Updata();
}

int Game::Draw()
{
	scene->Draw();
	return true;
}

Game::~Game()
{
}
