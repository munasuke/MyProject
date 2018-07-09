#pragma once
class NowLoading {
public:
	NowLoading();
	~NowLoading();

	void Updata();
	void Draw(int x, int y);
private:
	int loadH;
	int rot;
};

