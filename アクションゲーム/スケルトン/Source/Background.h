#pragma once
#include <memory>

class Camera;

//�w�i����N���X
class Background
{
public:
	Background(std::weak_ptr<Camera> cam);
	~Background();

	void Updata();//�w�i���X�V
	void Draw(const int sizex);//�w�i�`��
private:
	int bgH;
	positin pos;

	std::weak_ptr<Camera> camera;
};

