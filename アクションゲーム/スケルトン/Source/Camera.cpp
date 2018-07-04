#include "Camera.h"
#include "Stage.h"
#include "Player.h"
#include "Game.h"

Camera::Camera(std::weak_ptr<Stage> stage) : _stage(stage), _range(_stage.lock()->GetStageRange()) {
}


Camera::~Camera() {
}

void Camera::Update() {
	_range = _stage.lock()->GetStageRange();//ステージの範囲を取得
	auto _size = Game::Instance().GetScreenSize();//画面サイズを取得
	_pos = (_focus.lock())->GetPos();//フォーカス対象の座標を取得

	//カメラ座標の補正
	if (_pos.x - _size.w / 2 < _range.Left()){
		_pos.x = _range.Left() + _size.w / 2;
	}
	else if ( _pos.x + _size.w / 2 > _range.Right()){
		_pos.x = _range.Right() - _size.w / 2;
	}

	if(_pos.x < 0)
	{
		_pos.x = 0;
	}

	printf("%d\n", _pos.x);
}

//フォーカス対象を設定
void Camera::SetFocus(std::weak_ptr<Player> obj) {
	_focus = obj;
}

//カメラの座標を返す
const positin & Camera::GetPosition() const {
	return _pos;
}

//現在見えている範囲を返す
const Rect & Camera::GetViewport() const {
	return _range;
}

//受け取ったポジションをカメラに収まるように修正する
positin Camera::Correction(const positin & pos) {
	positin tmp = pos;	

	tmp.x -= _pos.x - 780 / 2;//カメラの移動分ひく

	return tmp;
}
