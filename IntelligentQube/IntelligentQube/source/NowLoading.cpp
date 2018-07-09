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
		printf("ƒ[ƒh‰æ‘œ‚ª“Ç‚İ‚Ü‚ê‚Ä‚¢‚Ü‚¹‚ñ\n");
	}
	rot++;
	DrawRotaGraph(x, y, 0.5f, rot * DX_PI_F / 180.0f, loadH, true);
}
