#include "DxLib.h"
#include "DeadMan.h"




DeadMan::DeadMan()
{
	pos = { 150, 300 };
	velocity = { 2, 0 };
	turnFlag = true;
	Load("Action/deadman.act");
	std::string path = "Action/" + header.pathName;
	image = LoadGraph(path.c_str());
	mode = "Walk";
}


DeadMan::~DeadMan()
{
}

void DeadMan::Updata()
{
}

void DeadMan::Draw()
{
	DrawRectRotaGraph2(pos.x, pos.y,
		cut[mode][_currentCutIndex].rect.pos.x, cut[mode][_currentCutIndex].rect.pos.y,
		cut[mode][_currentCutIndex].rect.Width(), cut[mode][_currentCutIndex].rect.Height(),
		cut[mode][_currentCutIndex].centor.x, cut[mode][_currentCutIndex].centor.y,
		2.0f, 1.0f, image, true, turnFlag);
}
