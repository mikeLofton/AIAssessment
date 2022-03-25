#pragma once
#include "Actor.h"
class Fruit :
	public Actor
{
public:

	/// <param name="x">Fruit x position</param>
	/// <param name="y">Fruit y position</param>
	Fruit(float x, float y);

	void start() override;

	void draw() override;

	void onCollision(Actor* other) override;

private:
};

