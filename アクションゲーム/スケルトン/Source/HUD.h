#pragma once

//��ʏ�ɕ\�������uUI�v
class HUD
{
public:
	HUD(const Player& pl);
	~HUD();

	void Updata();
	void Draw(int sizey);
private:
	int barTopH;//��o�[��UI�摜�n���h��
	int barBottomH;//���o�[��UI�摜�n���h��
	const Player& _pl;//player�ւ̎Q��
	int _score;//�X�R�A
};

