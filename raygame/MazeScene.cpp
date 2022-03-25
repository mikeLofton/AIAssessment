#include "MazeScene.h"
#include "Player.h"
#include "Wall.h"
#include "Ghost.h"
#include "Transform2D.h"
#include "Fruit.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "AABBCollider.h"
#include "DynamicArray.h"

Maze::TileKey _ = Maze::TileKey::OPEN;
Maze::TileKey w = Maze::TileKey::WALL;
Maze::TileKey s = Maze::TileKey::MUD;
Maze::TileKey p = Maze::TileKey::PLAYER;
Maze::TileKey g = Maze::TileKey::GHOST;
Maze::TileKey f = Maze::TileKey::FRUIT1;
Maze::TileKey r = Maze::TileKey::FRUIT2;
Maze::TileKey u = Maze::TileKey::FRUIT3;
Maze::TileKey t = Maze::TileKey::FRUIT4;
Maze::TileKey o = Maze::TileKey::GOAL;

Maze::Maze()
{
	//Create the player
	


	TileKey map[Maze::HEIGHT][Maze::WIDTH] = {
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, f, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, r, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, w, w, w, w, w, w, w, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, w, w, w, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, _, _, _, w },
		{ w, _, _, _, _, _, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, _, _, _, w },
		{ w, _, _, _, _, _, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, _, _, _, w },
		{ _, _, _, _, _, _, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, _, _, _, _ },
		{ _, _, _, _, _, _, w, _, _, _, _, _, _, _, g, _, _, _, _, w, w, w, _, _, _, _, _, _ },
		{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, o, _, _, _, _, _, _, _, _, _, _, _, _, _ },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, u, _, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, t, _, w },
		{ w, _, _, _, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, _, _, w },
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
	};


	m_player = new Player(0, 0, "Player", 200, 50);
	m_ghost = new Ghost(0, 0, 200, 150, 0xFF6666FF, this);
	m_goal = new Actor(0, 0, "Goal");
	m_fruit1 = new Fruit(0, 0);
	m_fruit2 = new Fruit(0, 0);
	m_fruit3 = new Fruit(0, 0);
	m_fruit4 = new Fruit(0, 0);
	GameManager::getInstance()->init(m_ghost, m_goal, m_fruit1, m_fruit2, m_fruit3, m_fruit4);

	//Generate the map
	generate(map);
}

Maze::~Maze()
{
	delete m_player;
	for (int y = 0; y < m_size.y; y++) {
		for (int x = 0; x < m_size.x; x++) {
			delete m_grid[x][y].actor;
			delete m_grid[x][y].node;
		}
	}
}

void Maze::draw()
{
	//NodeGraph::drawGraph(m_grid[0][0].node);
	Scene::draw();
}

Maze::Tile Maze::getTile(MathLibrary::Vector2 position)
{
	int x = (int)(position.x / TILE_SIZE);
	int y = (int)(position.y / TILE_SIZE);
	if (x >= 0 && x < Maze::WIDTH && y >= 0 && y < Maze::HEIGHT)
		return m_grid[x][y];
	else
		return m_grid[0][0];
}

MathLibrary::Vector2 Maze::getPosition(Tile tile)
{
	return MathLibrary::Vector2{ tile.x * TILE_SIZE + (TILE_SIZE / 2.0f), tile.y * TILE_SIZE + (TILE_SIZE / 2.0f) };
}

Maze::Tile Maze::createTile(int x, int y, TileKey key)
{
	// Create a new tile at the given location
	Tile tile{ x, y };
	tile.node = new NodeGraph::Node();
	MathLibrary::Vector2 position = getPosition(tile);
	// Set the cost and actor of each tile
	switch (key) {
	case TileKey::OPEN:
		tile.cost = 1.0f;
		break;
	case TileKey::WALL:
		tile.cost = 100.0f;
		tile.actor = new Wall(position.x, position.y);
		tile.node->walkable = false;
		addActor(tile.actor);
		break;
	case TileKey::PLAYER:
		tile.cost = 1.0f;
		m_player->getTransform()->setWorldPostion(position);
		tile.actor = m_player;
		addActor(tile.actor);
		break;
	case TileKey::GHOST:
	{
		tile.cost = 1.0f;
		m_ghost->getTransform()->setWorldPostion(position);
		m_ghost->setTarget(m_fruit1);
		tile.actor = m_ghost;
		addActor(tile.actor);
		break;
	}
	case TileKey::FRUIT1:
	{
		tile.cost = 1.0f;
		m_fruit1->getTransform()->setWorldPostion(position);
		tile.actor = m_fruit1;	
		addActor(tile.actor);
		break;
	}
	case TileKey::FRUIT2:
	{
		tile.cost = 1.0f;
		m_fruit2->getTransform()->setWorldPostion(position);
		tile.actor = m_fruit2;
		addActor(tile.actor);
		break;
	}
	case TileKey::FRUIT3:
	{
		tile.cost = 1.0f;
		m_fruit3->getTransform()->setWorldPostion(position);
		tile.actor = m_fruit3;
		addActor(tile.actor);
		break;
	}
	case TileKey::FRUIT4:
	{
		tile.cost = 1.0f;
		m_fruit4->getTransform()->setWorldPostion(position);
		tile.actor = m_fruit4;
		addActor(tile.actor);
		break;
	}
	case TileKey::GOAL:
	{
		tile.cost = 1.0f;
		m_goal->getTransform()->setWorldPostion(position);
		m_goal->addComponent(new SpriteComponent("Images/bullet.png"));
		m_goal->getTransform()->setScale({ TILE_SIZE + 50, TILE_SIZE + 50});
		m_goal->setCollider(new AABBCollider(Maze::TILE_SIZE, Maze::TILE_SIZE, m_goal));
		tile.actor = m_goal;
		addActor(tile.actor);
		break;
	}
	}
	return tile;
}

void Maze::generate(TileKey map[Maze::HEIGHT][Maze::WIDTH])
{
	for (int y = 0; y < m_size.y; y++) {
		for (int x = 0; x < m_size.x; x++) {
			// Create the tile
			Tile currentTile = createTile(x, y, map[y][x]);
			// Add node to graph
			currentTile.node->position = getPosition(currentTile);
			if (x > 0) { // west connection
				Tile other = m_grid[x - 1][y];
				currentTile.node->edges.addItem(NodeGraph::Edge{ other.node, other.cost });
				other.node->edges.addItem(NodeGraph::Edge{ currentTile.node, currentTile.cost });
			}
			if (y > 0) { // north connection
				Tile other = m_grid[x][y - 1];
				currentTile.node->edges.addItem(NodeGraph::Edge{ other.node, other.cost });
				other.node->edges.addItem(NodeGraph::Edge{ currentTile.node, currentTile.cost });
			}
			// Set the tile on the grid
			m_grid[x][y] = currentTile;
		}
	}
}