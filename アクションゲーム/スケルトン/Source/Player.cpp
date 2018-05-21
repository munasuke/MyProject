#include "Player.h"
#include "DxLib.h"

using namespace DxLib;

Player::Player()
{
	velocity = { 2, 0 };
	pos = { 50, 300 };
	turnFlag = false;
	_jump = false;

	Load("Action/player.act");
	std::string path = "Action/" + header.pathName;

	for (int i = 0; i < 256; i++) {
		key[i] = 0;
		old_key[i] = 0;
	}
	_updata = &Player::NeutralUpdata;
	image = LoadGraph(path.c_str());
	mode = "Walk";
}


Player::~Player()
{
}

void Player::Updata()
{
	for (int i = 0; i < 256; i++) {
		old_key[i] = key[i];
	}
	GetHitKeyStateAll(key);
	
	//アクション↓
	pos.y += velocity.y;
	velocity.y += (int)gravity;
	(this->*_updata)();
	if (pos.y >= 340) {
		pos.y = 340;
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
	if (mode == "Jump") {
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

	DrawFormatString(10, 70, 0xff0000, "%d, %d", GetPos());
	DrawFormatString(10, 90, 0xff0000, "%d, %d", GetVec());
}


void Player::Jump() {
	int jump_power = -17;
	if (!_jump) {
		_jump = true;
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
	if (key[KEY_INPUT_NUMPAD4] || key[KEY_INPUT_NUMPAD6]) {
		_updata = &Player::WalkUpdata;
		ChangeMode("Walk");
	}
	else if (key[KEY_INPUT_NUMPAD2]) {
		Crouch();
	}
	else if (key(KEY_INPUT_Z)) {
		Punch();
	}
	if (key(KEY_INPUT_NUMPAD8)) {
		Jump();
	}
}

void Player::WalkUpdata()
{
	if (key[KEY_INPUT_NUMPAD4]) {
		turnFlag = true;
		pos.x -= velocity.x;
	}
	else if (key[KEY_INPUT_NUMPAD6]) {
		turnFlag = false;
		pos.x += velocity.x;
	}
	else {
		_updata = &Player::NeutralUpdata;
	}
	if (key(KEY_INPUT_NUMPAD8)) {
		Jump();
	}
	if (key(KEY_INPUT_Z)) {
		Punch();
	}
	
}

void Player::JumpUpdata()
{
	if (!_jump) {
		return;
	}
	if (key[KEY_INPUT_NUMPAD2]) {
		_jump = false;
		Crouch();
	}
	if (pos.y >= 340) {
		_jump = false;
		_updata = &Player::NeutralUpdata;
		ChangeMode("Walk");
	}
}

void Player::CrouchUpdata()
{
	if (key(KEY_INPUT_Z)) {
		Kick();
	}
	if (key(KEY_INPUT_NUMPAD8)) {
		Jump();
	}
	if (key[KEY_INPUT_NUMPAD2] == 0) {
		_updata = &Player::NeutralUpdata;
		ChangeMode("Walk");
	}
	if (key(KEY_INPUT_X)) {
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
	if (_currentCutIndex > cut[mode].size() - 1) {
		_updata = &Player::CrouchUpdata;
		ChangeMode("Crouch");
	}
}

void Player::SlidingUpdata()
{
	pos.x += turnFlag ? -5.0f : 5.0f;
	if (_currentCutIndex > cut[mode].size() - 1) {
		_updata = &Player::CrouchUpdata;
		ChangeMode("Crouch");
	}
}

void Player::DamageUpdata()
{
	
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
