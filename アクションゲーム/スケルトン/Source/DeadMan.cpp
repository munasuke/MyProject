#include "DxLib.h"
#include "DeadMan.h"
#include "Player.h"




DeadMan::DeadMan() : speed(1)
{
	pos = { 300, 340 };
	velocity = { 2, 0 };
	turnFlag = true;
	Load("Action/deadman.act");
	std::string path = "Action/" + header.pathName;
	image = LoadGraph(path.c_str());
	mode = "Walk";
	_updata = &DeadMan::NeutralUpdata;
	pl = new Player();
}


DeadMan::~DeadMan()
{
	delete pl;
}

void DeadMan::Updata()
{
	//(this->*_updata)();
}

void DeadMan::Draw()
{
	int centorX = turnFlag ? cut[mode][_currentCutIndex].rect.Width() - cut[mode][_currentCutIndex].centor.x : cut[mode][_currentCutIndex].centor.x;

	DrawRectRotaGraph2(pos.x, pos.y,
		cut[mode][_currentCutIndex].rect.Left(), cut[mode][_currentCutIndex].rect.Top(),
		cut[mode][_currentCutIndex].rect.Width(), cut[mode][_currentCutIndex].rect.Height(),
		centorX, cut[mode][_currentCutIndex].centor.y,
		2.0, 0.0, image, true, turnFlag);

	if (_flame > cut[mode][_currentCutIndex].frame) {
		_currentCutIndex++;
		_flame = 0;
	}

	DrawRect();

	if (_currentCutIndex > cut[mode].size() - 1) {
		_currentCutIndex = 0;
	}
	_flame++;

	DrawFormatString(10, 110, 0xff00ff00, "%d", turnFlag);
	DrawFormatString(10, 130, 0xff00ff00, "%s", mode);
}

void DeadMan::NeutralUpdata()
{
	if (pl->GetPos().x > pos.x) {
		_updata = &DeadMan::WalkUpdata;
		ChangeMode("Walk");
	}
	else {
		_updata = &DeadMan::WalkUpdata;
		ChangeMode("Walk");
	}
}

void DeadMan::WalkUpdata()
{
	if (pl->GetPos().x >= pos.x) {
		turnFlag = false;
		pos.x += speed;
		_updata = &DeadMan::NeutralUpdata;
	}
	else {
		turnFlag = true;
		pos.x -= speed;
		_updata = &DeadMan::NeutralUpdata;
	}
}

void DeadMan::DieUpdata()
{
}
