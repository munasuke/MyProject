#include "NowLoading.h"
#include "DxLib.h"


NowLoading::NowLoading() :
	loadH(LoadGraph("img/loading.png")),
	rot(0)
{
}


NowLoading::~NowLoading() {
}

void NowLoading::Updata() {
}

void NowLoading::Draw(int x, int y) {
	if (loadH == -1){
		printf("ロード画像が読み込まれていません\n");
	}
	rot++;
	DrawRotaGraph(x, y, 0.1f, rot * DX_PI_F / 180.0f, loadH, true);
}
