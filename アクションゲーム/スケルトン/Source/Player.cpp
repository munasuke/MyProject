#include "Player.h"
#include "DxLib.h"



Player::Player() :
	_flame(0),
	_currentCutIndex(0),
	velocity({ 2, 0 }),
	pos({ 50, 300 }),
	turnFlag(false),
	gravity(1.0f),
	_jump(false)
{
	data.clear();
	cut.clear();
	Load();
	std::string path = "Action/" + header.pathName;

	for (int i = 0; i < 256; i++) {
		key[i] = 0;
		old_key[i] = 0;
	}
	_updata = &Player::NeutralUpdata;
	player = LoadGraph(path.c_str());
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

	DrawRectRotaGraph2(pos.x, pos.y, cut[mode][_currentCutIndex].rect.Left(), cut[mode][_currentCutIndex].rect.Top(), cut[mode][_currentCutIndex].rect.Width(), cut[mode][_currentCutIndex].rect.Height(), centorX, cut[mode][_currentCutIndex].centor.y, 2.0, 0, player, true, turnFlag);
	if (_flame > cut[mode][_currentCutIndex].frame) {
		_currentCutIndex++;
		_flame = 0;
	}
	//最終インデックスか確認
	if (mode == "Jump") {
		if (_currentCutIndex > cut[mode].size() - 2) {
			_currentCutIndex = 2;
		}
	}
	if (_currentCutIndex > cut[mode].size() - 1) {
		if (mode != "Punch" && mode != "Kick") {
			_currentCutIndex = 0;//ループ
		}
	}
	if (_updata != &Player::NeutralUpdata) {
		_flame++;
	}
}

void Player::Load()
{
	FILE* file;
	fopen_s(&file, "Action/player.act", "rb");
	fread(&header.version, sizeof(header.version),1, file );

	fread(&header.filePathNameNum, sizeof(int), 1, file);

	header.pathName.resize(header.filePathNameNum);
	fread(&header.pathName[0], header.filePathNameNum, 1, file);

	fread(&header.actionDateNum, sizeof(int), 1, file);

	ImageDate dummy = {};
	for (int i = 0; i < header.actionDateNum; ++i) {
		fread(&dummy.actionNameNum, sizeof(dummy.actionNameNum), 1, file);

		dummy.actionName.resize(dummy.actionNameNum);
		fread(&dummy.actionName[0], dummy.actionNameNum, 1, file);

		fread(&dummy.loop, sizeof(dummy.loop), 1, file);

		fread(&dummy.count, sizeof(dummy.count), 1, file);

		data[i] = dummy;

		cut[dummy.actionName].resize(dummy.count);
		for (int j = 0; j < dummy.count; ++j) {
			fread(&cut[dummy.actionName][j], sizeof(cut[dummy.actionName][j]), 1, file);

			int num = 0;
			fread(&num, sizeof(int), 1, file);

			attackRect[dummy.actionName].resize(num);
			for (int k = 0; k < num; ++k) {
				fread(&attackRect[dummy.actionName][k], sizeof(attackRect[dummy.actionName][k]), 1, file);
			}
		}
	}
	fclose(file);
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
	if (key(KEY_INPUT_NUMPAD8) && pos.y == 340) {
		Jump();
	}
	if (key[KEY_INPUT_NUMPAD2] == 0) {
		_updata = &Player::NeutralUpdata;
		ChangeMode("Walk");
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

void Player::DamageUpdata()
{
}

//状態切り替え
void Player::ChangeMode(std::string md)
{
	_flame = 0;
	_currentCutIndex = 0;
	mode = md;
}

positin Player::GetPos()
{
	return pos;
}

positin Player::GetVec()
{
	return velocity;
}
