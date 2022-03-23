#include "Fruit.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "MazeScene.h"
#include "AABBCollider.h"

Fruit::Fruit(float x, float y) : Actor(x, y, "Fruit")
{
}

void Fruit::start()
{
	Actor::start();

	addComponent(new SpriteComponent("Images/Cherry.png"));
	getTransform()->setScale({ Maze::TILE_SIZE, Maze::TILE_SIZE });
	setCollider(new AABBCollider(Maze::TILE_SIZE, Maze::TILE_SIZE, this));
}
