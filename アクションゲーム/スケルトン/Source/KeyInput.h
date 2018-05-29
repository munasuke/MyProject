#pragma once

class KeyInput
{
public:
	KeyInput();
	~KeyInput();

	void Updata();
	bool IsPressing(int id)const;
private:
	int keyState;
	int keyStateOld;
};

