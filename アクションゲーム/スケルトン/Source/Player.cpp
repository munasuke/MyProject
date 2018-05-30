#include "Player.h"
#include "DxLib.h"

using namespace DxLib;

Player::Player(std::weak_ptr<KeyInput> _key) : _walk(false), ground(340), key(_key)
{
	velocity = { 0, 0 };
	pos = { 50, 300 };
	turnFlag = false;
	_jump = false;
	speed = 2;

	Load("Action/player.act");
	std::string path = "Action/" + header.pathName;

	_updata = &Player::NeutralUpdata;
	image = LoadGraph(path.c_str());
	mode = "Walk";
	_damageSE = LoadSoundMem("se/p_damage.wav");
	_damageTime = 0;
}


Player::~Player()
{
}

void Player::Updata()
{	
	//アクション↓
	pos += velocity;
	velocity.y += (int)gravity;
	(this->*_updata)();
	if (pos.y >= ground) {
		pos.y = ground;
	}
}

void Player::Draw()
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

	//最終インデックスか確認
	if (mode == "Jump"|| mode == "Damage") {
		if (_currentCutIndex > cut[mode].size() - 2) {
			_currentCutIndex = 2;
		}
	}
	if (_currentCutIndex > cut[mode].size() - 1) {
		if (mode != "Punch" && mode != "Kick" && mode != "Sliding") {
			_currentCutIndex = 0;//ループ
		}
	}
	if (_updata != &Player::NeutralUpdata) {
		_flame++;
	}
}


void Player::Jump() {
	int jump_power = -15;
	if (!_jump) {
		_jump = true;
		if (_walk) {
			velocity.x = turnFlag ? -speed : speed;
		}
		velocity.y = jump_power;
		_updata = &Player::JumpUpdata;
		ChangeMode("Jump");
	}
}

void Player::Crouch()
{
	_updata = &Player::CrouchUpdata;
	ChangeMode("Crouch");
}

void Player::Punch()
{
	_updata = &Player::PunchUpdata;
	ChangeMode("Punch");
}

void Player::Kick()
{
	_updata = &Player::KickUpdata;
	ChangeMode("Kick");
}

void Player::Sliding()
{
	//着地間際に下方向に入力しながら攻撃ボタンを入力
	_updata = &Player::SlidingUpdata;
	ChangeMode("Sliding");
}

void Player::NeutralUpdata()
{
	if (pos.y >= ground) {
		velocity.x = 0;
	}
	if (key.lock()->IsPressing(PAD_INPUT_LEFT) || key.lock()->IsPressing(PAD_INPUT_RIGHT)) {
		_updata = &Player::WalkUpdata;
		mode = "Walk";
	}
	else if (key.lock()->IsPressing(PAD_INPUT_DOWN)) {
		Crouch();
	}
	else if (key.lock()->IsTrigger(PAD_INPUT_1)) {
		Punch();
	}
	if (key.lock()->IsTrigger(PAD_INPUT_UP)) {
		Jump();
	}
}

void Player::WalkUpdata()
{
	if (key.lock()->IsPressing(PAD_INPUT_LEFT)) {
		turnFlag = true;
		pos.x -= speed;
	}
	else if (key.lock()->IsPressing(PAD_INPUT_RIGHT)) {
		turnFlag = false;
		pos.x += speed;
	}
	else {
		_updata = &Player::NeutralUpdata;
	}
	if (key.lock()->IsTrigger(PAD_INPUT_UP)) {
		_walk = true;
		Jump();
	}
	if (key.lock()->IsTrigger(PAD_INPUT_1)) {
		Punch();
	}
	
}

void Player::JumpUpdata()
{
	_walk = false;
	if (!_jump) {
		return;
	}
	if (key.lock()->IsPressing(PAD_INPUT_DOWN)) {
		_jump = false;
		Crouch();
	}
	if (pos.y >= ground) {
		velocity.x = 0;
		_jump = false;
		_updata = &Player::NeutralUpdata;
		ChangeMode("Walk");
	}
}

void Player::CrouchUpdata()
{
	if (pos.y >= ground) {
		velocity.x = 0;
	}
	if (key.lock()->IsTrigger(PAD_INPUT_1)) {
		Kick();
	}
	if (key.lock()->IsTrigger(PAD_INPUT_UP)) {
		Jump();
	}
	if (key.lock()->IsPressing(PAD_INPUT_DOWN) == 0) {
		_updata = &Player::NeutralUpdata;
		ChangeMode("Walk");
	}
	if (key.lock()->IsTrigger(PAD_INPUT_2)) {
		Sliding();
	}
}

void Player::PunchUpdata()
{
	if (_currentCutIndex > cut[mode].size() - 1) {
		_updata = &Player::NeutralUpdata;
		ChangeMode("Walk");
	}
}

void Player::KickUpdata()
{
	if (pos.y >= ground) {
		velocity.x = 0;
	}
	if (_currentCutIndex > cut[mode].size() - 1) {
		_updata = &Player::CrouchUpdata;
		ChangeMode("Crouch");
	}
}

void Player::SlidingUpdata()
{
	if (pos.y >= ground) {
		velocity.x = 0;
	}
	pos.x += turnFlag ? -5.0f : 5.0f;
	if (_currentCutIndex > cut[mode].size() - 1) {
		_updata = &Player::CrouchUpdata;
		ChangeMode("Crouch");
	}
}

void Player::DamageUpdata()
{
	--_damageTime;
	pos.x += turnFlag ? 1.0f : -1.0f;
	if (_damageTime < 0) {
		_damageTime = 0;
		_updata = &Player::NeutralUpdata;
		ChangeMode("Walk");
	}
}


positin Player::GetPos()
{
	return pos;
}

positin Player::GetVec()
{
	return velocity;
}

std::vector<AttackRect> Player::GetActRect()
{
	return attackRect[mode][_currentCutIndex];
}

void Player::Damage()
{
	_jump = false;
	_damageTime = 30;
	_updata = &Player::DamageUpdata;
	ChangeMode("Damage");
	PlaySoundMem(_damageSE, DX_PLAYTYPE_BACK);
}

std::string Player::GetActMode()
{
	return mode;
}
