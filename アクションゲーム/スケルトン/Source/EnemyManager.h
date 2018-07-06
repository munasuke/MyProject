#pragma once

#include "CharactorObject.h"
#include "DeadMan.h"
#include "Bat.h"
#include "Pike.h"
#include "Player.h"
#include <memory>
#include <list>
#include <map>
#include <string>

class Camera;

//“G‚Ì¶¬‚Æ”jŠü‚ğ‘€‚éƒNƒ‰ƒX
class EnemyManager
{
public:
	~EnemyManager();
	static EnemyManager* GetInstance() {
		return instance;
	}
	static void Create() {
		if (instance == nullptr) {
			instance = new EnemyManager();
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
	void Summons(std::string name, std::weak_ptr<Player>pl, std::weak_ptr<Camera> cam, positin pos);
private:
	EnemyManager();
	static EnemyManager* instance;

	std::list<std::shared_ptr<CharactorObject>> enemy;
	std::map<std::string, std::shared_ptr<CharactorObject>> _enemy;
};

