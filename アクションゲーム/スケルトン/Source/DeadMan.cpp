#include "DxLib.h"
#include "DeadMan.h"
#include "Camera.h"




DeadMan::DeadMan(std::weak_ptr<Player>pl, std::weak_ptr<Camera> cam, positin _pos) : pl(pl), die(false)
{
	pos = _pos;
	velocity = { 1, 0 };
	turnFlag = true;
	speed = 1;
	Load("Action/deadman.act");
	std::string path = "Action/" + header.pathName;
	image = LoadGraph(path.c_str());
	mode = "Walk";
	_updata = &DeadMan::NeutralUpdata;
	_wait = 0;
	_damageSE = LoadSoundMem("se/e_gusha.mp3");
	life = 1;
	camera = cam;
}


DeadMan::~DeadMan()
{
	
}

void DeadMan::Updata()
{
	(this->*_updata)();
	IsHitPlayer();
}

void DeadMan::Draw()
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

	DrawRect(localPos);

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

	if (_updata != &DeadMan::NeutralUpdata) {
		_flame++;
	}
}

bool DeadMan::GetDie()
{
	return die;
}

void DeadMan::NeutralUpdata()
{
	if (localPos.x > pl.lock()->GetLocalPos().x) {
		turnFlag = true;
		_updata = &DeadMan::WalkUpdata;
		_wait = 60;
	}
	else {
		turnFlag = false;
		_updata = &DeadMan::WalkUpdata;
		_wait = 60;
	}
}

void DeadMan::WalkUpdata()
{
	--_wait;
	pos.x += turnFlag ? -speed : speed;
	if (_wait < 0) {
		_updata = &DeadMan::NeutralUpdata;
	}
}

void DeadMan::DieUpdata()
{
	die = true;
}

void DeadMan::DamageUpdata()
{
	--_wait;
	if (_wait < 0) {
		_wait = 0;
		_updata = &DeadMan::NeutralUpdata;
		ChangeMode("Walk");
	}
}

void DeadMan::Damage()
{
	if (pl.lock()->GetActMode() == "Punch") {
		life--;
		if (life != 0) {
			ChangeMode("Damage");
			_wait = 15;
			_updata = &DeadMan::DamageUpdata;
		}
		else {
			ChangeMode("Die");
			_wait = 30;
			_updata = &DeadMan::DieUpdata;
		}
	}
	else if (pl.lock()->GetActMode() == "Kick" || pl.lock()->GetActMode() == "Sliding") {
		ChangeMode("Die");
		_wait = 30;
		_updata = &DeadMan::DieUpdata;
	}
	pos.x += turnFlag ? 10 : -10;
	PlaySoundMem(_damageSE, DX_PLAYTYPE_BACK);
}

void DeadMan::IsHitPlayer()
{
	if (mode == "Damge" || mode == "Die" || pl.lock()->GetActMode() == "Damage") {
		return;
	}
	for (auto& prec : pl.lock()->GetActRect()) {
		for (auto& erec : attackRect[mode][_currentCutIndex]) {
			if (IsCollision(prec, erec, pl.lock()->GetLocalPos(), localPos)) {
				if (prec.type == RectType::attack && erec.type == RectType::damage) {
					Damage();
				}
				else if (prec.type == RectType::damage && erec.type == RectType::attack) {
					pl.lock()->Damage();
				}
			}	
		}
	}
}
