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

void EnemyManager::Summons(std::string name, std::weak_ptr<Player> pl, positin pos)
{
	if (name == "DeadMan") {
		//DeadMan
		_enemy["DeadMan"] = std::make_shared<DeadMan>(pl, pos);
		enemy.push_back(_enemy["DeadMan"]);
	}
	else if (name == "Bat") {
		//Bat
		_enemy["Bat"] = std::make_shared<Bat>(pl, pos);
		enemy.push_back(_enemy["Bat"]);
	}
}

EnemyManager::EnemyManager()
{
	enemy.clear();
}


EnemyManager::~EnemyManager()
{
}
