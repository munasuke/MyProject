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

	void SetFocus(std::weak_ptr<Player> obj);//フォーカスするオブジェクトを設定

	const positin& GetPosition() const;//カメラの座標を返す
	
	const Rect& GetViewport() const;//現在見えている範囲を返す

	positin Correction(const positin& pos);//カメラに収まるように修正する

private:
	std::weak_ptr<Stage> _stage;
	std::weak_ptr<Player> _focus;
	positin _pos;
	Rect _range;
};

