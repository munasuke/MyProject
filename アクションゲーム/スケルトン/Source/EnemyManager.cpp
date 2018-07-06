#include "EnemyManager.h"
#include "Typedef.h"
#include "Camera.h"

EnemyManager *EnemyManager::instance = nullptr;//‰Šú‰»

//“GupdataŒÄ‚Ô
void EnemyManager::Updata()
{
	for(auto itr = enemy.begin(); itr != enemy.end(); itr++){
		(*itr)->Updata();
	}
}

//“GdrawŒÄ‚Ô
void EnemyManager::Draw()
{
	for(auto itr = enemy.begin(); itr != enemy.end(); itr++){
		(*itr)->Draw();
	}
}

void EnemyManager::Summons(std::string name, std::weak_ptr<Player> pl, std::weak_ptr<Camera> cam, positin pos)
{
	if (name == "DeadMan") {
		//DeadMan
		_enemy["DeadMan"] = std::make_shared<DeadMan>(pl, cam, pos);
		enemy.push_back(_enemy["DeadMan"]);
	}
	else if (name == "Bat") {
		//Bat
		_enemy["Bat"] = std::make_shared<Bat>(pl, cam, pos);
		enemy.push_back(_enemy["Bat"]);
	}
	else if (name == "Pike") {
		_enemy["Pike"] = std::make_shared<Pike>(pl, cam, pos);
		enemy.push_back(_enemy["Pike"]);
	}
}

EnemyManager::EnemyManager()
{
	enemy.clear();
}


EnemyManager::~EnemyManager()
{
}
