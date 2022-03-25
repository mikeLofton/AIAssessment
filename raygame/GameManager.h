#pragma once
#include <Vector2.h>
class Fruit;
class Actor;
class Ghost;

class GameManager
{
public:
	/// <summary>
	/// Gives the Game manager a reference to the ghost, goal, and fruits
	/// </summary>
	void init(Ghost* ghost, Actor* goal, Fruit* fruit1, Fruit* fruit2, Fruit* fruit3, Fruit* fruit4);

	/// <summary>
	/// Gets an instance of the game manager
	/// </summary>
	static GameManager* getInstance();

	/// <returns>Returns the ghost</returns>
	Ghost* getGhost() { return m_ghost; }

	/// <returns>Return fruit 1</returns>
	Fruit* getFruit1() { return m_fruit1; }
	/// <returns>Returns fruit2</returns>
	Fruit* getFruit2() { return m_fruit2; }
	/// <returns>Returns fruit4</returns>
	Fruit* getFruit3() { return m_fruit3; }
	/// <returns>Returns fruit4</returns>
	Fruit* getFruit4() { return m_fruit4; }
	void setFruit(Fruit* fruit) { m_fruit1 = fruit; }
	/// <returns>Returns goal</returns>
	Actor* getGoal() { return m_goal; }

	static int m_fruitNum; //The number of fruit in the scene

private:
	static GameManager* m_instance;
	Ghost* m_ghost;
	Fruit* m_fruit1;
	Fruit* m_fruit2;
	Fruit* m_fruit3;
	Fruit* m_fruit4;
	Actor* m_goal;
};

