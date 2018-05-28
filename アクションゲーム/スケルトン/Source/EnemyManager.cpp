#include "EnemyManager.h"

EnemyManager *EnemyManager::instance = nullptr;//‰Šú‰»

//“GupdataŒÄ‚Ô
void EnemyManager::Updata()
{
	dm->Updata();
	bat->Updata();
}

//“GdrawŒÄ‚Ô
void EnemyManager::Draw()
{
	//for(auto itr = enemy.begin(); itr != enemy.end(); itr++){
	//	itr->Draw();
	//}
	dm->Draw();
	bat->Draw();
}

EnemyManager::EnemyManager(std::weak_ptr<Player>pl)
{
	dm = std::make_shared<DeadMan>(pl);
	bat = std::make_shared<Bat>(pl);
}


EnemyManager::~EnemyManager()
{
}
