#include "StateMachineComponent.h"
#include "Actor.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "PathfindComponent.h"
#include "Transform2D.h"
#include "Fruit.h"
#include "GameManager.h"
#include "Ghost.h"

void StateMachineComponent::start()
{
	Component::start();

	m_pathfindComp = getOwner()->getComponent<PathfindComponent>();

	m_wanderComponent = getOwner()->getComponent<WanderComponent>();
	m_wanderForce = m_wanderComponent->getSteeringForce();

	m_currentState = IDLE;
}

void StateMachineComponent::update(float deltaTime)
{
	Component::update(deltaTime);

	switch (m_currentState)
	{
	case IDLE:
		m_pathfindComp->setEnabled(false);
		m_wanderComponent->setSteeringForce(0);

		if (GameManager::getInstance()->getFruit1()->getActive())
			setCurrentState(SEEKFRUIT);

		break;
	case SEEKFRUIT:
		m_pathfindComp->setEnabled(true);
		m_wanderComponent->setSteeringForce(0);

		if (GameManager::getInstance()->getFruit1()->getActive())
			m_pathfindComp->setTarget(GameManager::getInstance()->getFruit1());
		else if (GameManager::getInstance()->getFruit2()->getActive())
			m_pathfindComp->setTarget(GameManager::getInstance()->getFruit2());
		else if (GameManager::getInstance()->getFruit3()->getActive())
			m_pathfindComp->setTarget(GameManager::getInstance()->getFruit3());
		else if (GameManager::getInstance()->getFruit4()->getActive())
			m_pathfindComp->setTarget(GameManager::getInstance()->getFruit4());

		if (GameManager::getInstance()->getGhost()->getHasFruit())
			setCurrentState(SEEKGOAL);

		break;
	case SEEKGOAL:
		m_pathfindComp->setEnabled(true);
		m_wanderComponent->setSteeringForce(0);
		m_pathfindComp->setTarget(GameManager::getInstance()->getGoal());

		if (GameManager::m_fruitNum > 0 && GameManager::getInstance()->getGhost()->getHasFruit() == false)
			setCurrentState(SEEKFRUIT);
		else if (GameManager::getInstance()->getGhost()->getHasFruit() == false && GameManager::m_fruitNum <= 0)
			setCurrentState(WANDERMAZE);

		break;

	case WANDERMAZE:
		m_pathfindComp->setEnabled(false);
		m_wanderComponent->setSteeringForce(300);

		if (GameManager::getInstance()->getFruit1()->getActive())
			setCurrentState(SEEKFRUIT);

		break;
	}
}
