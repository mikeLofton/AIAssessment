#pragma once
#include <Vector2.h>
class Fruit;
class Actor;
class Ghost;

class GameManager
{
public:
	void init(Ghost* ghost, Actor* goal, Fruit* fruit1, Fruit* fruit2, Fruit* fruit3, Fruit* fruit4);
	static GameManager* getInstance();
	Ghost* getGhost() { return m_ghost; }
	Fruit* getFruit1() { return m_fruit1; }
	Fruit* getFruit2() { return m_fruit2; }
	Fruit* getFruit3() { return m_fruit3; }
	Fruit* getFruit4() { return m_fruit4; }
	void setFruit(Fruit* fruit) { m_fruit1 = fruit; }
	Actor* getGoal() { return m_goal; }

	static int m_fruitNum;

private:
	static GameManager* m_instance;
	Ghost* m_ghost;
	Fruit* m_fruit1;
	Fruit* m_fruit2;
	Fruit* m_fruit3;
	Fruit* m_fruit4;
	Actor* m_goal;
};

