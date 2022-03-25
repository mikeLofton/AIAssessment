#include "Fruit.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include "MazeScene.h"
#include "AABBCollider.h"
#include "Ghost.h"

Fruit::Fruit(float x, float y) : Actor(x, y, "Fruit")
{
}

void Fruit::start()
{
	Actor::start();

	addComponent(new SpriteComponent("Images/Cherry.png")); //Add the cherry sprite
	getTransform()->setScale({ Maze::TILE_SIZE + 10, Maze::TILE_SIZE + 10}); //Scale the sprite by tile size plus 10
	setCollider(new AABBCollider(Maze::TILE_SIZE, Maze::TILE_SIZE, this)); //Add the collider
}

void Fruit::draw()
{
	Actor::draw();

	getCollider()->draw();
}

void Fruit::onCollision(Actor* other)
{
	
}
