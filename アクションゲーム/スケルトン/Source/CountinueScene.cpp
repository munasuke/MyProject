#include "Typedef.h"
#include "CountinueScene.h"
#include "Game.h"
#include "GameplayingScene.h"
#include "GameoverScene.h"
#include "DxLib.h"


CountinueScene::CountinueScene(std::weak_ptr<KeyInput> _key) :
	cntImage(LoadGraph("img/count.png")),
	flame(0),
	fadeFlag(false)
{
	key = _key;
	alpha = 0;
	bgm = LoadSoundMem("bgm/bgm1.mp3");
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
	printf("Countinue Scene\n");
}


CountinueScene::~CountinueScene()
{
	StopSoundMem(bgm);
	printf("Countinue Scene is Deleted\n\n");
}

void CountinueScene::Updata()
{
	if (flame < time * (count_max - 1)) {
		if (key.lock()->IsTrigger(PAD_INPUT_1)) {
			flame += time - (flame % time);
		}
		if (key.lock()->IsTrigger(PAD_INPUT_8)) {//コンティニュー
			fadeFlag = true;
			scene = new GameplayingScene(key);
		}
	}
	else {//ゲームオーバー
		fadeFlag = true;
		scene = new GameoverScene(key);
	}
	FadeOut();
}

void CountinueScene::Draw()
{
	FadeIn();
	if (flame < time * (count_max - 1)) {
		flame++;
	}
	DrawRectGraph(300, 150, count_size.x * ((flame / time) % count.x), count_size.y * ((flame / (time * count.x)) % count.y), count_size.x, count_size.y, cntImage, true, false);
}

void CountinueScene::FadeIn()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	if (!fadeFlag) {
		if (alpha < 256) {
			alpha += 2;
		}
	}
}

void CountinueScene::FadeOut()
{
	if (!fadeFlag) {
		return;
	}
	if (alpha >= 0) {
		alpha-=2;
		if (alpha == 0) {
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			Game::Instance().ChangeScene(scene);
		}
	}
}
