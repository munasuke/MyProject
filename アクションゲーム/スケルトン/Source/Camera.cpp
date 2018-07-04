#include "Camera.h"
#include "Stage.h"
#include "Player.h"
#include "Game.h"

Camera::Camera(std::weak_ptr<Stage> stage) : _stage(stage), _range(_stage.lock()->GetStageRange()) {
}


Camera::~Camera() {
}

void Camera::Update() {
	_range = _stage.lock()->GetStageRange();//�X�e�[�W�͈̔͂��擾
	auto _size = Game::Instance().GetScreenSize();//��ʃT�C�Y���擾
	_pos = (_focus.lock())->GetPos();//�t�H�[�J�X�Ώۂ̍��W���擾

	//�J�������W�̕␳
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

//�t�H�[�J�X�Ώۂ�ݒ�
void Camera::SetFocus(std::weak_ptr<Player> obj) {
	_focus = obj;
}

//�J�����̍��W��Ԃ�
const positin & Camera::GetPosition() const {
	return _pos;
}

//���݌����Ă���͈͂�Ԃ�
const Rect & Camera::GetViewport() const {
	return _range;
}

//�󂯎�����|�W�V�������J�����Ɏ��܂�悤�ɏC������
positin Camera::Correction(const positin & pos) {
	positin tmp = pos;	

	tmp.x -= _pos.x - 780 / 2;//�J�����̈ړ����Ђ�

	return tmp;
}
