#include "EnemyManager.h"

EnemyManager *EnemyManager::instance = nullptr;//������

//�Gupdata�Ă�
void EnemyManager::Updata()
{
	dm->Updata();
	bat->Updata();
}

//�Gdraw�Ă�
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
