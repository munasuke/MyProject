#include "DxLib.h"
#include "Typedef.h"
#include "Background.h"
#include "Camera.h"

Background::Background(std::weak_ptr<Camera> cam) : camera(cam)
{
	bgH = LoadGraph("img/splatterhouse.png");
}

Background::~Background()
{
}

void Background::Updata()
{
	pos = camera.lock()->GetPosition();
}

void Background::Draw(const int sizex)
{
	//”wŒiƒXƒNƒ[ƒ‹
	for (int i = 0; i < 5; i+=2) {
		DrawGraph(-pos.x + 576 * i, 0, bgH, true);
		DrawTurnGraph(-pos.x + 576 * (i + 1), 0, bgH, true);
	}

#ifdef _DEBUG
	DrawLine(0, 340, sizex, 340, 0x00ff00);
#endif
}
