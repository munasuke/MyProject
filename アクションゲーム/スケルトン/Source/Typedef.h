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

//ヘッダー
struct Header {
	float version;//バージョン
	int filePathNameNum;//pathの文字列数
	std::string pathName;//pathの名前
	int actionDateNum;//アクションデータ数
};

//アクションデータ
struct ImageDate {
	int actionNameNum;//アクションデータの文字列数
	std::string actionName;//アクションの名前
	char loop;//ループ
	int count;//カウント
};

//分割データ
struct CutDate {
	Rect rect;//切り抜き矩形
	positin centor;//画像中心
	int frame;//継続時間
};

enum class RectType {
	anchor,//アンカー
	attack,//攻撃矩形
	damage//やられ矩形
};

//攻撃用
struct AttackRect {
	RectType type;//矩形種別
	Rect rect;//矩形情報
};

