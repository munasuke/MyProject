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
		printf("���[�h�摜���ǂݍ��܂�Ă��܂���\n");
	}
	rot++;
	DrawRotaGraph(x, y, 0.5f, rot * DX_PI_F / 180.0f, loadH, true);
}
