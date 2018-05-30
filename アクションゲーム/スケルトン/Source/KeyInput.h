#pragma once

class KeyInput
{
public:
	KeyInput();
	~KeyInput();

	void Updata();
	bool IsPressing(int id)const;//‰Ÿ‚µ‚Ä‚éŠÔˆ—
	bool IsTrigger(int id)const;//ƒgƒŠƒK[ˆ—
private:
	int keyState;
	int keyStateOld;
};

