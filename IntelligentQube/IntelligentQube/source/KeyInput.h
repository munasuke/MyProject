#pragma once

class KeyInput
{
public:
	KeyInput();
	~KeyInput();

	void Updata();
	bool IsPressing(int id)const;//押してる間処理
	bool IsTrigger(int id)const;//トリガー処理
private:
	int keyState;
	int keyStateOld;
};

