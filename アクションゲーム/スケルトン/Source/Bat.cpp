#include "Bat.h"
#include "DxLib.h"


Bat::Bat(std::weak_ptr<Player>pl) : pl(pl), die(false), _flySE(LoadSoundMem("se/habataki.mp3")), range({200, 0})
{
	pos = { 700, 130 };
	velocity = { 1, 0 };
	turnFlag = true;
	speed = 5;
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
	(this->*_updata)();
	IsHitPlayer();
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

	if (_currentCutIndex > cut[mode].size() - 1) {
		_currentCutIndex = 0;
	}

	if (_updata != &Bat::NeutralUpdata) {
		_flame++;
	}
#ifdef _DEBUG
	DrawBox(pos.x - range.x, pos.y - 50, pos.x, pos.y, 0xff0000ff, false);
	DrawBox(pos.x, pos.y - 50, pos.x + range.x, pos.y, 0xff0000ff, false);
#endif
}

void Bat::NeutralUpdata()
{
	if ((pl.lock()->GetPos().x <= pos.x && pl.lock()->GetPos().x >= pos.x - range.x)
	 || (pl.lock()->GetPos().x >= pos.x && pl.lock()->GetPos().x <= pos.x + range.x)) {
		velocity.x = (pos.x >= pl.lock()->GetPos().x ? -speed : speed);
		range.y = pl.lock()->GetPos().y - 70;
		Fly();
	}
}

void Bat::FlyUpdata()
{
	if (pos.y <= range.y) {//çÇÇ≥ÇçáÇÌÇπÇÈ
		pos.y += 2;
	}
	else {
		pos.x += velocity.x;
	}
}

void Bat::DieUpdata()
{
	if (pos.y < 340) {
		pos.y += speed;
		pos.x += turnFlag ? 1 : -1;
	}
	die = true;
}

void Bat::Fly()
{
	_updata = &Bat::FlyUpdata;
	ChangeMode("Fly");
}

void Bat::Damage()
{
	_updata = &Bat::DieUpdata;
	ChangeMode("Die");
	PlaySoundMem(_damageSE, DX_PLAYTYPE_BACK);
}

void Bat::IsHitPlayer()
{
	if (mode == "Damge" || mode == "Die") {
		return;
	}
	for (auto& prec : pl.lock()->GetActRect()) {
		for (auto& erec : attackRect[mode][_currentCutIndex]) {
			if (IsCollision(prec, erec, pl.lock()->GetPos(), pos)) {
				if (prec.type == RectType::attack && erec.type == RectType::damage) {
					Damage();
					printf("Ç†ÇΩÇË\n");
				}
				else if (prec.type == RectType::damage && erec.type == RectType::attack) {
					pl.lock()->Damage();
					printf("É_ÉÅÅ[ÉW\n");
				}
			}
		}
	}
}
