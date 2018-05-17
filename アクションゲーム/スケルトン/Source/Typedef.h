#pragma once
#include <string>
template <typename T>
struct Vector2D{
	Vector2D()
	{}
	Vector2D(T inx, T iny) : x(inx), y(iny)
	{}

	T x;
	T y;

	Vector2D operator+(T i)
	{
		Vector2D tmp;
		tmp.x = x + i;
		tmp.y = y + i;
		return tmp;
	}
	Vector2D operator+(Vector2D& vec) {
		Vector2D tmp;
		tmp.x = x + vec.x;
		tmp.y = y + vec.y;
		return tmp;
	}
	void operator+=(T i) {
		x += i;
		y += i;
	}
	void operator+=(Vector2D& vec) {
		x += vec.x;
		y += vec.y;
	}
};

typedef Vector2D<int>positin;

struct Rect {
	positin pos;
	int w, h;
	Rect() : pos(0, 0), w(0), h(0) {};
	Rect(int x, int y, int inw, int inh) : pos(x, y), w(inw), h(inh) {};
	Rect(positin& inpos, int inw, int inh) : pos(inpos), w(inw), h(inh) {};

	void SetPos(int x, int y) {
		pos.x = x;
		pos.y = y;
	}
	void SetPos(const positin& inpos) {
		pos.x = inpos.x;
		pos.y = inpos.y;
	}
	positin GetPos() {
		return pos;
	}
	int Left()const { return pos.x - w / 2; }
	int Top()const { return pos.y - h / 2; }
	int Right()const { return pos.x + w / 2; }
	int Bottom()const { return pos.y + h / 2; }
	int Width()const { return w; }
	int Height()const { return h; }
};

//�w�b�_�[
struct Header {
	float version;//�o�[�W����
	int filePathNameNum;//path�̕�����
	std::string pathName;//path�̖��O
	int actionDateNum;//�A�N�V�����f�[�^��
};

//�A�N�V�����f�[�^
struct ImageDate {
	int actionNameNum;//�A�N�V�����f�[�^�̕�����
	std::string actionName;//�A�N�V�����̖��O
	char loop;//���[�v
	int count;//�J�E���g
};

//�����f�[�^
struct CutDate {
	Rect rect;//�؂蔲����`
	positin centor;//�摜���S
	int frame;//�p������
};

enum class RectType {
	anchor,//�A���J�[
	attack,//�U����`
	damage//�����`
};

//�U���p
struct AttackRect {
	RectType type;//��`���
	Rect rect;//��`���
};

