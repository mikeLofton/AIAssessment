#include "GameManager.h"
#include "Actor.h"
#include "Fruit.h"
#include "Ghost.h"

GameManager* GameManager::m_instance = nullptr;

void GameManager::init(Ghost* ghost, Fruit* fruit, Actor* goal)
{
	m_ghost = ghost;
	m_fruit = fruit;
	m_goal = goal;
}

GameManager* GameManager::getInstance()
{
	if (!m_instance)
		m_instance = new GameManager();

	return m_instance;
}
