#pragma once
#include <memory>

class Camera;

//”wŒi§ŒäƒNƒ‰ƒX
class Background
{
public:
	Background(std::weak_ptr<Camera> cam);
	~Background();

	void Updata();//”wŒiî•ñXV
	void Draw(const int sizex);//”wŒi•`‰æ
private:
	int bgH;
	positin pos;

	std::weak_ptr<Camera> camera;
};

