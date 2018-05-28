#include "EnemyManager.h"

EnemyManager *EnemyManager::instance = nullptr;//初期化

//敵updata呼ぶ
void EnemyManager::Updata()
{
	dm->Updata();
	bat->Updata();
}

//敵draw呼ぶ
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
