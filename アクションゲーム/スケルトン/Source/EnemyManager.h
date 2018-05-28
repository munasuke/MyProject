#pragma once
#include "DeadMan.h"
#include "Bat.h"
#include "Player.h"
#include <memory>
#include <list>

//“G‚Ì¶¬‚Æ”jŠü‚ğ‘€‚éƒNƒ‰ƒX
class EnemyManager
{
public:
	~EnemyManager();
	static EnemyManager* GetInstance() {
		return instance;
	}
	static void Create(std::weak_ptr<Player>pl) {
		if (instance == nullptr) {
			instance = new EnemyManager(pl);
		}
	}
	static void Destroy() {
		if (instance != nullptr) {
			delete instance;
		}
		instance = nullptr;
	}

	void Updata();
	void Draw();
private:
	EnemyManager(std::weak_ptr<Player>pl);
	static EnemyManager* instance;
	std::shared_ptr<DeadMan> dm;
	std::shared_ptr<Bat> bat;
};

