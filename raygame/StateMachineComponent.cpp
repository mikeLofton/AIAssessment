#include "StateMachineComponent.h"
#include "Actor.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "PathfindComponent.h"
#include "Transform2D.h"
#include "Fruit.h"

void StateMachineComponent::start()
{
	Component::start();

	m_seekComponent = getOwner()->getComponent<SeekComponent>();
	m_seekForce = m_seekComponent->getSteeringForce();

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

		if (m_fruit->getActive())
			setCurrentState(SEEKFRUIT);

		break;
	case SEEKFRUIT:
		

		break;
	case SEEKGOAL:

		break;

	case WANDERMAZE:

		break;
	}
}
