#pragma once

#include <memory>
#include "Typedef.h"

class Player;
class Stage;

class Camera {
public:
	Camera(std::weak_ptr<Stage> stage);
	~Camera();

	void Update();

	void SetFocus(std::weak_ptr<Player> obj);//�t�H�[�J�X����I�u�W�F�N�g��ݒ�

	const positin& GetPosition() const;//�J�����̍��W��Ԃ�
	
	const Rect& GetViewport() const;//���݌����Ă���͈͂�Ԃ�

	positin Correction(const positin& pos);//�J�����Ɏ��܂�悤�ɏC������

private:
	std::weak_ptr<Stage> _stage;
	std::weak_ptr<Player> _focus;
	positin _pos;
	Rect _range;
};

