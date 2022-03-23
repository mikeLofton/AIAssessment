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

		if (GameManager::getInstance()->getFruit()->getActive())
			setCurrentState(SEEKFRUIT);

		break;
	case SEEKFRUIT:
		m_pathfindComp->setEnabled(true);
		m_wanderComponent->setSteeringForce(0);
		m_pathfindComp->setTarget(GameManager::getInstance()->getFruit());

		if (GameManager::getInstance()->getGhost()->getHasFruit())
			setCurrentState(SEEKGOAL);

		break;
	case SEEKGOAL:
		m_pathfindComp->setEnabled(true);
		m_wanderComponent->setSteeringForce(0);
		m_pathfindComp->setTarget(GameManager::getInstance()->getGoal());

		if (GameManager::getInstance()->getGhost()->getHasFruit() == false && GameManager::getInstance()->getFruit()->getActive())
			setCurrentState(SEEKFRUIT);
		else if (GameManager::getInstance()->getGhost()->getHasFruit() == false && GameManager::getInstance()->getFruit()->getActive() == false)
			setCurrentState(WANDERMAZE);

		break;

	case WANDERMAZE:
		m_pathfindComp->setEnabled(false);
		m_wanderComponent->setSteeringForce(300);

		if (GameManager::getInstance()->getFruit()->getActive())
			setCurrentState(SEEKFRUIT);

		break;
	}
}
