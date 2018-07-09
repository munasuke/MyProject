#include "Ladder.h"
#include "Player.h"
#include "Camera.h"
#include "Load.h"
#include "DxLib.h"


Ladder::Ladder(std::weak_ptr<Player> _pl, std::weak_ptr<Camera> _cam, positin _pos) :
	pl(_pl)
{
	camera = _cam;
	pos = _pos;
	Load("Action/event.act");
	std::string path = "Action/" + header.pathName;
	image = Load::GetInstance()->LoadImg(path.c_str());
	mode = "Ladder";
}


Ladder::~Ladder()
{
}

void Ladder::Updata()
{
	auto right = camera.lock()->GetViewport().Right();
	auto left = camera.lock()->GetViewport().Left();
	pos.x = min(max(pos.x, left), right);

	localPos = camera.lock()->Correction(pos);

	if (pl.lock()->GetLocalPos().x >= localPos.x - 10) {
		if (pl.lock()->GetActMode() != "Climb") {
			pl.lock()->SetActMode("Climb");
		}
	}
}

void Ladder::Draw()
{
	int centorX =
		turnFlag ? cut[mode][_currentCutIndex].rect.Width() - cut[mode][_currentCutIndex].centor.x : cut[mode][_currentCutIndex].centor.x;


	DrawRectRotaGraph2(localPos.x, localPos.y,
		cut[mode][_currentCutIndex].rect.Left(), cut[mode][_currentCutIndex].rect.Top(),
		cut[mode][_currentCutIndex].rect.Width(), cut[mode][_currentCutIndex].rect.Height(),
		cut[mode][_currentCutIndex].centor.x, cut[mode][_currentCutIndex].centor.y,
		2.0, 0.0, image, true, false);

	if (_flame > cut[mode][_currentCutIndex].frame) {
		_currentCutIndex++;
		_flame = 0;
	}

	DrawRect(localPos);

	if (_currentCutIndex > cut[mode].size() - 1) {
		_currentCutIndex = 0;


	}
	_flame++;
}
