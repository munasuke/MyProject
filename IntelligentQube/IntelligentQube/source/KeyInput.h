#pragma once

class KeyInput
{
public:
	KeyInput();
	~KeyInput();

	void Updata();
	bool IsPressing(int id)const;//�����Ă�ԏ���
	bool IsTrigger(int id)const;//�g���K�[����
private:
	int keyState;
	int keyStateOld;
};

