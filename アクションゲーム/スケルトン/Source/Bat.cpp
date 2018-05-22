#include "Bat.h"
#include "DxLib.h"


Bat::Bat(std::weak_ptr<Player>pl) : pl(pl), speed(2), die(false), _flySE(LoadSoundMem("se/habataki.mp3"))
{
	pos = { 400, 100 };
	velocity = { 1, 0 };
	turnFlag = true;
	Load("Action/bat.act");
	std::string path = "Action/" + header.pathName;
	image = LoadGraph(path.c_str());
	mode = "Wait";
	_updata = &Bat::NeutralUpdata;
	_wait = 0;
	_damageSE = LoadSoundMem("se/bird_damage.mp3");
}


Bat::~Bat()
{
}

void Bat::Updata()
{
}

void Bat::Draw()
{
	int centorX =
		turnFlag ? cut[mode][_currentCutIndex].rect.Width() - cut[mode][_currentCutIndex].centor.x : cut[mode][_currentCutIndex].centor.x;

	DrawRectRotaGraph2(pos.x, pos.y,
		cut[mode][_currentCutIndex].rect.Left(), cut[mode][_currentCutIndex].rect.Top(),
		cut[mode][_currentCutIndex].rect.Width(), cut[mode][_currentCutIndex].rect.Height(),
		centorX, cut[mode][_currentCutIndex].centor.y,
		2.0, 0.0, image, true, turnFlag);

	if (_flame > cut[mode][_currentCutIndex].frame) {
		if (mode != "Die")
		{
			_currentCutIndex++;
		}
		else
		{
			if (cut[mode].size() - 1 > _currentCutIndex)
			{
				_currentCutIndex++;
			}
		}

		_flame = 0;
	}

	DrawRect();

	if (mode == "Damage") {
		if (_currentCutIndex > cut[mode].size() - 2) {
			_currentCutIndex = 2;
		}
	}

	if (_currentCutIndex > cut[mode].size() - 1) {
		if (mode != "Die") {
			_currentCutIndex = 0;
		}
	}

	if (_updata != &Bat::NeutralUpdata) {
		_flame++;
	}
}

void Bat::NeutralUpdata()
{
}

void Bat::FlyUpdata()
{
}

void Bat::DieUpdata()
{
}

void Bat::Damage()
{
}

void Bat::IsHitPlayer()
{
}
