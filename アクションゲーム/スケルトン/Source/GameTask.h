#pragma once
#include "Singleton.h"

#define SCREEN_SIZE_X (768)
#define SCREEN_SIZE_Y (448)

// モード
enum GMODE {
	GMODE_NON,
	GMODE_SYSINIT,
	GMODE_GAMEINIT,
	GMODE_GAME,
	GMODE_DESTROY,
	GMODE_MAX
};

class GameTask:public osaru::Singleton<GameTask>
{
	friend osaru::Singleton<GameTask>;
public:
	~GameTask();
	void Updata(void);
	void Draw(void);
private:
	GMODE mode;
	GameTask();
	int SysInit(void);
	int GameInit(void);
	int GameMain(void);
	int GameUpdate(void);
	int GameDraw(void);
	int GameDestroy(void);
};

