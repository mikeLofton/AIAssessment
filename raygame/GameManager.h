#pragma once
#include <Vector2.h>
class Fruit;
class Actor;
class Ghost;

class GameManager
{
public:
	void init(Ghost* ghost, Actor* goal);
	static GameManager* getInstance();
	Ghost* getGhost() { return m_ghost; }
	Fruit* getFruit() { return m_fruit; }
	void setFruit(Fruit* fruit) { m_fruit = fruit; }
	Actor* getGoal() { return m_goal; }

	static int m_fruitNum;

private:
	static GameManager* m_instance;
	Ghost* m_ghost;
	Fruit* m_fruit;
	Actor* m_goal;
};

