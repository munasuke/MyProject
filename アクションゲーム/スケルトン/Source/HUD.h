#pragma once
#include <memory>

class Player;

//��ʏ�ɕ\�������uUI�v
class HUD
{
public:
	HUD(std::weak_ptr<Player> pl);
	~HUD();

	void Updata();
	void Draw(int sizey);
private:
	int barTopH;//��o�[��UI�摜�n���h��
	int barBottomH;//���o�[��UI�摜�n���h��
	int heartH;//���C�t�摜�n���h��
	std::weak_ptr<Player> _pl;
	int _score;//�X�R�A
};

