#include "DxLib.h"
#include "DeadMan.h"




DeadMan::DeadMan(std::weak_ptr<Player>pl) : pl(pl), die(false)
{
	pos = { 300, 340 };
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
	life = 3;
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
	if (pos.x > pl.lock()->GetPos().x) {
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
			if (IsCollision(prec, erec, pl.lock()->GetPos(), pos)) {
				if (prec.type == RectType::attack && erec.type == RectType::damage) {
					Damage();
					printf("‚ ‚½‚è\n");
				}
				else if (prec.type == RectType::damage && erec.type == RectType::attack) {
					pl.lock()->Damage();
					printf("ƒ_ƒ[ƒW\n");
				}
			}	
		}
	}
}
