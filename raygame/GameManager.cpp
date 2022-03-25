#include "GameManager.h"
#include "Actor.h"
#include "Fruit.h"
#include "Ghost.h"

GameManager* GameManager::m_instance = nullptr;
int GameManager::m_fruitNum = 4;

void GameManager::init(Ghost* ghost, Actor* goal, Fruit* fruit1, Fruit* fruit2, Fruit* fruit3, Fruit* fruit4)
{
	m_ghost = ghost;
	m_goal = goal;
	m_fruit1 = fruit1;
	m_fruit2 = fruit2;
	m_fruit3 = fruit3;
	m_fruit4 = fruit4;
}

GameManager* GameManager::getInstance()
{
	if (!m_instance)
		m_instance = new GameManager();

	return m_instance;
}
