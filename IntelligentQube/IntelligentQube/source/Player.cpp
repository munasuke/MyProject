#include "Player.h"
#include "KeyInput.h"


Player::Player(std::weak_ptr<KeyInput> _key) :
	key(_key),
	onceflag(true),
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
	if (onceflag){
		onceflag = false;
		animIndex = MV1AttachAnim(playerH, 1, -1);
		animTime = 0.0f;
		animTimeTotal = MV1GetAttachAnimTotalTime(playerH, animTime);
	}

	Move();
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

void Player::Move() {
	if (key.lock()->IsPressing(PAD_INPUT_UP) && key.lock()->IsPressing(PAD_INPUT_RIGHT)){
		rot.y = RAD(225);
	}
	else if (key.lock()->IsPressing(PAD_INPUT_UP) && key.lock()->IsPressing(PAD_INPUT_LEFT)){
		rot.y = RAD(135);
	}
	else if (key.lock()->IsPressing(PAD_INPUT_DOWN) && key.lock()->IsPressing(PAD_INPUT_RIGHT)){
		rot.y = RAD(315);
	}
	else if (key.lock()->IsPressing(PAD_INPUT_DOWN) && key.lock()->IsPressing(PAD_INPUT_LEFT)){
		rot.y = RAD(45);
	}
	else{
		if (key.lock()->IsPressing(PAD_INPUT_UP)){
			pos.z += speed;
			rot.y = RAD(180);
		}
		else if (key.lock()->IsPressing(PAD_INPUT_DOWN)){
			pos.z -= speed;
			rot.y = RAD(0);
		}
		else if (key.lock()->IsPressing(PAD_INPUT_RIGHT)){
			pos.x += speed;
			rot.y = RAD(270);
		}
		else if (key.lock()->IsPressing(PAD_INPUT_LEFT)){
			pos.x -= speed;
			rot.y = RAD(90);
		}
	}
}

void Player::Animation() {
	animTime += 0.5f;
	if (animTime > animTimeTotal){
		animTime = 0.0f;
	}
	MV1SetAttachAnimTime(playerH, animIndex, animTime);
}
