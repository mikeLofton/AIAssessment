#pragma once
#include "Actor.h"
class Fruit :
	public Actor
{
public:
	Fruit(float x, float y);

	void start() override;
private:
};

