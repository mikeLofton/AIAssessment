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

		//If fruit1 is active set the seek behavior
		if (GameManager::getInstance()->getFruit1()->getActive())
			setCurrentState(SEEKFRUIT);

		break;
	case SEEKFRUIT:
		m_pathfindComp->setEnabled(true);
		m_wanderComponent->setSteeringForce(0);

		if (GameManager::getInstance()->getFruit1()->getActive()) //If fruit1 is active target fruit 1
			m_pathfindComp->setTarget(GameManager::getInstance()->getFruit1());
		else if (GameManager::getInstance()->getFruit2()->getActive())
			m_pathfindComp->setTarget(GameManager::getInstance()->getFruit2()); //If fruit2 is active target fruit2
		else if (GameManager::getInstance()->getFruit3()->getActive())
			m_pathfindComp->setTarget(GameManager::getInstance()->getFruit3()); //If fruit 3 is active target frutit3
		else if (GameManager::getInstance()->getFruit4()->getActive())
			m_pathfindComp->setTarget(GameManager::getInstance()->getFruit4()); //If fruit4 is active target fruit4

		if (GameManager::getInstance()->getGhost()->getHasFruit()) //If the ghost has a fruit enter seek goal state.
			setCurrentState(SEEKGOAL);

		break;
	case SEEKGOAL:
		m_pathfindComp->setEnabled(true);
		m_wanderComponent->setSteeringForce(0);
		m_pathfindComp->setTarget(GameManager::getInstance()->getGoal()); //Set target to goal

		//If there are more than zero fruits and the ghost doesn't have a fruit
		if (GameManager::m_fruitNum > 0 && GameManager::getInstance()->getGhost()->getHasFruit() == false)
			setCurrentState(SEEKFRUIT); //Enter seek fruit state
		//If the ghost doen't have a fruit and there are zero fruits
		else if (GameManager::getInstance()->getGhost()->getHasFruit() == false && GameManager::m_fruitNum <= 0)
			setCurrentState(WANDERMAZE); //Enter wander state

		break;

	case WANDERMAZE:
		m_pathfindComp->setEnabled(false);
		m_wanderComponent->setSteeringForce(300);

		//If a fruit is in the maze enter seek state
		if (GameManager::getInstance()->getFruit1()->getActive())
			setCurrentState(SEEKFRUIT);

		break;
	}
}
