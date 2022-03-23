#pragma once
#include "Actor.h"
class Fruit :
	public Actor
{
public:
	Fruit(float x, float y);

	void start() override;

	void draw() override;

	void onCollision(Actor* other) override;

private:
};

