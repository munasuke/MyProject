#include "Pike.h"
#include "Player.h"
#include "Camera.h"
#include "Load.h"
#include "DxLib.h"


Pike::Pike(std::weak_ptr<Player> _pl, std::weak_ptr<Camera> _cam, positin _pos) :
	pl(_pl)
{
	camera = _cam;
	pos = _pos;
	Load("Action/pike.act");
	std::string path = "Action/" + header.pathName;
	image = Load::GetInstance()->LoadImg(path.c_str());
	mode = "Attack";
	turnFlag = false;
}


Pike::~Pike()
{
}

void Pike::Updata()
{
	IsHitPlayer();
}

void Pike::Draw()
{
	int centorX =
		turnFlag ? cut[mode][_currentCutIndex].rect.Width() - cut[mode][_currentCutIndex].centor.x : cut[mode][_currentCutIndex].centor.x;

	auto right = camera.lock()->GetViewport().Right();
	auto left = camera.lock()->GetViewport().Left();
	pos.x = min(max(pos.x, left), right);

	localPos = camera.lock()->Correction(pos);

	DrawRectRotaGraph2(localPos.x, localPos.y,
		cut[mode][_currentCutIndex].rect.Left(), cut[mode][_currentCutIndex].rect.Top(),
		cut[mode][_currentCutIndex].rect.Width(), cut[mode][_currentCutIndex].rect.Height(),
		centorX, cut[mode][_currentCutIndex].centor.y,
		2.0, 0.0, image, true, turnFlag);

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

void Pike::IsHitPlayer()
{
	if (pl.lock()->GetActMode() == "Damage") {
		return;
	}
	for (auto& prec : pl.lock()->GetActRect()) {
		for (auto& erec : attackRect[mode][_currentCutIndex]) {
			if (IsCollision(prec, erec, pl.lock()->GetLocalPos(), localPos)) {
				if (prec.type == RectType::damage && erec.type == RectType::attack) {
					pl.lock()->Damage();
				}
			}
		}
	}
}
