#include "Player.h"
#include "KeyInput.h"
#include "DxLib.h"


Player::Player(std::weak_ptr<KeyInput> _key) :
	updata(&Player::NeutralUpdata),
	key(_key),
	pos({ 0.0f, 0.0f, 0.0f }),
	rot({ 0.0f, 0.0f, 0.0f }),
	speed(0.5f)
{
	//非同期読み込み
	SetUseASyncLoadFlag(true);
	playerH = MV1LoadModel("models/KK/キタキツネ.pmx");
}


Player::~Player() {
}

void Player::Updata() {
	if (CheckHandleASyncLoad(playerH)){
		return;
	}
	static bool onceflag = true;
	if (onceflag){
		onceflag = false;
		anim = {
			{"Wait", 0 },
			{"Walk", 1 }
		};
		animIndex = MV1AttachAnim(playerH, anim["Wait"], -1);
		animTime = 0.0f;
		animTimeTotal = MV1GetAttachAnimTotalTime(playerH, static_cast<int>(animTime));
	}
	(this->*updata)();
	Animation();
}

void Player::Draw() {
	if (CheckHandleASyncLoad(playerH)){
		return;
	}
	if (playerH == -1){
		printf("ロードされてないよ\n");
	}
	MV1SetPosition(playerH, VGet(pos.x, pos.y, pos.z));
	MV1SetRotationXYZ(playerH, VGet(rot.x, rot.y, rot.z));
	MV1DrawModel(playerH);
}

int Player::GetPlayerHandle() {
	return playerH;
}

positin3D Player::GetPosition() {
	return pos;
}

void Player::Move() {
}

void Player::Animation() {
	animTime += 0.5f;
	if (animTime > animTimeTotal){
		animTime = 0.0f;
	}
	MV1SetAttachAnimTime(playerH, animIndex, animTime);
}

void Player::SetAnimation(std::string state)
{
	MV1DetachAnim(playerH, animIndex);
	animIndex = MV1AttachAnim(playerH, anim[state]);
	animTime = 0;
}

void Player::NeutralUpdata()
{
	if (key.lock()->IsPressing(PAD_INPUT_UP)
		|| key.lock()->IsPressing(PAD_INPUT_DOWN)
		|| key.lock()->IsPressing(PAD_INPUT_RIGHT)
		|| key.lock()->IsPressing(PAD_INPUT_LEFT)) {
		SetAnimation("Walk");
		updata = &Player::WalkUpdata;
	}
}

void Player::WalkUpdata()
{
	if (key.lock()->IsPressing(PAD_INPUT_UP) && key.lock()->IsPressing(PAD_INPUT_RIGHT)) {
		rot.y = RAD(225);
		pos.x += cos(RAD(315)) * speed;
		pos.z -= sin(RAD(315)) * speed;
	}
	else if (key.lock()->IsPressing(PAD_INPUT_UP) && key.lock()->IsPressing(PAD_INPUT_LEFT)) {
		rot.y = RAD(135);
		pos.x += cos(RAD(225)) * speed;
		pos.z -= sin(RAD(225)) * speed;
	}
	else if (key.lock()->IsPressing(PAD_INPUT_DOWN) && key.lock()->IsPressing(PAD_INPUT_RIGHT)) {
		rot.y = RAD(315);
		pos.x += cos(RAD(45)) * speed;
		pos.z -= sin(RAD(45)) * speed;
	}
	else if (key.lock()->IsPressing(PAD_INPUT_DOWN) && key.lock()->IsPressing(PAD_INPUT_LEFT)) {
		rot.y = RAD(45);
		pos.x += cos(RAD(135)) * speed;
		pos.z -= sin(RAD(135)) * speed;
	}
	else {
		if (key.lock()->IsPressing(PAD_INPUT_UP)) {
			pos.z += speed;
			rot.y = RAD(180);
		}
		else if (key.lock()->IsPressing(PAD_INPUT_DOWN)) {
			pos.z -= speed;
			rot.y = RAD(0);
		}
		else if (key.lock()->IsPressing(PAD_INPUT_RIGHT)) {
			pos.x += speed;
			rot.y = RAD(270);
		}
		else if (key.lock()->IsPressing(PAD_INPUT_LEFT)) {
			pos.x -= speed;
			rot.y = RAD(90);
		}
		else {
			SetAnimation("Wait");
			updata = &Player::NeutralUpdata;
		}
	}
}
