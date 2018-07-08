#include "Player.h"
#include "Camera.h"
#include "DxLib.h"

using namespace DxLib;

Player::Player(std::weak_ptr<KeyInput> _key, std::weak_ptr<Camera> _camera) : 
	_walk(false), 
	ground(340), 
	key(_key), 
	_life(5), 
	_ultimateTime(-1), 
	dieFlag(false),
	_alpha(255),
	_aFlag(false),
	_deathTime(110)
{
	velocity = { 0, 0 };
	pos = { 50, 300 };
	turnFlag = false;
	_jump = false;
	speed = 2;

	Load("Action/player.act");
	std::string path = "Action/" + header.pathName;

	se["Attack"] = LoadSoundMem("se/punch-swing.mp3");
	se["Sliding"] = LoadSoundMem("se/sliding.mp3");
	se["Damage"] = LoadSoundMem("se/p_damage.wav");
	se["Death"] = LoadSoundMem("se/death_voice.mp3");

	_updata = &Player::NeutralUpdata;
	image = LoadGraph(path.c_str());
	mode = "Walk";
	_damageTime = 0;

	camera = _camera;
}


Player::~Player()
{
}

void Player::Updata()
{	
	(this->*_updata)();
	if (mode == "Climb") {
		_updata = &Player::LadderUpdata;
	}
	else {
		//アクション↓
		pos += velocity;
		velocity.y += (int)gravity;
		if (pos.y >= ground) {
			pos.y = ground;
		}
		_ultimateTime--;
	}
}

void Player::Draw()
{
	int centorX = turnFlag ? cut[mode][_currentCutIndex].rect.Width() - cut[mode][_currentCutIndex].centor.x : cut[mode][_currentCutIndex].centor.x;

	auto right = camera.lock()->GetViewport().Right();
	auto left = camera.lock()->GetViewport().Left();
	pos.x = min(max(pos.x, left), right);

	auto i = camera.lock()->Correction(pos);
	localPos = i;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	//無敵中は点滅する
	if (_life > 0) {
		if (_ultimateTime >= 0) {
			_alpha = _aFlag ? 255 : 0;
			_aFlag = !_aFlag;
		}
		else {
			_aFlag = false;
			_alpha = 255;
		}
	}

	DrawRectRotaGraph2(i.x, pos.y,
		cut[mode][_currentCutIndex].rect.Left(), cut[mode][_currentCutIndex].rect.Top(),
		cut[mode][_currentCutIndex].rect.Width(), cut[mode][_currentCutIndex].rect.Height(),
		centorX, cut[mode][_currentCutIndex].centor.y,
		2.0, 0.0, image, true, turnFlag);

	if (_flame > cut[mode][_currentCutIndex].frame) {
		_currentCutIndex++;
		_flame = 0;
	}

	DrawRect(i);

	//最終インデックスか確認
	if (mode == "Jump"|| mode == "Damage") {
		if (_currentCutIndex > cut[mode].size() - 2) {
			_currentCutIndex = 2;
		}
	}
	if (_currentCutIndex > cut[mode].size() - 1) {
		if (mode != "Punch" && mode != "Kick" && mode != "Sliding" && mode != "Die") {
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
	PlaySoundMem(se["Attack"], DX_PLAYTYPE_BACK);
	_updata = &Player::PunchUpdata;
	ChangeMode("Punch");
}

void Player::Kick()
{
	PlaySoundMem(se["Attack"], DX_PLAYTYPE_BACK);
	_updata = &Player::KickUpdata;
	ChangeMode("Kick");
}

void Player::Sliding()
{
	PlaySoundMem(se["Sliding"], DX_PLAYTYPE_BACK);
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

void Player::DieUpdata() {
	printf("Die\n");
	if (_currentCutIndex > cut[mode].size() - 2) {
		_currentCutIndex = cut[mode].size() - 1;
	}
	if (_deathTime >= 0) {
		--_deathTime;
	}
	else {
		dieFlag = true;
	}
}

void Player::LadderUpdata()
{
	pos.y -= speed;
}


positin Player::GetPos()
{
	return pos;
}

positin Player::GetLocalPos() {
	return localPos;
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
	if (_ultimateTime >= 0){
		return;
	}

	_ultimateTime = 120;//無敵2秒

	//--_life;
	printf("%d\n", _life);
	if (_life > 0) {
		_jump = false;
		_damageTime = 30;
		_updata = &Player::DamageUpdata;
		ChangeMode("Damage");
		PlaySoundMem(se["Damage"], DX_PLAYTYPE_BACK);
	}
	else {//死
		PlaySoundMem(se["Death"], DX_PLAYTYPE_BACK);
		_updata = &Player::DieUpdata;
		ChangeMode("Die");
	}
}

std::string Player::GetActMode()
{
	return mode;
}

void Player::SetActMode(std::string name)
{
	mode = name;
	ChangeMode(name);
}

int Player::GetLife()
{
	return _life;
}

bool Player::GetDieFlag() {
	return dieFlag;
}
