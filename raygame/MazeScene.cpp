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
Maze::TileKey f = Maze::TileKey::FRUIT;
Maze::TileKey o = Maze::TileKey::GOAL;

Maze::Maze()
{
	//Create the player
	


	TileKey map[Maze::HEIGHT][Maze::WIDTH] = {
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
		{ w, _, _, _, _, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, _, _, w },
		{ w, _, f, _, _, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, f, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, w, w, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, w, w, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _ },
		{ _, _, _, _, _, _, _, _, _, _, _, _, w, _, g, _, w, _, _, _, _, _, _, _, _, _, _, _ },
		{ _, _, _, _, _, _, _, _, _, _, _, _, w, _, o, _, w, _, _, _, _, _, _, _, _, _, _, _ },
		{ w, _, _, _, _, _, _, _, _, _, _, _, w, _, _, _, w, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, w, w, w, w, w, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, w, w, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, w, w, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w },
		{ w, _, f, _, _, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, f, _, w },
		{ w, _, _, _, _, w, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, _, w, _, _, _, _, w },
		{ w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w },
	};


	m_player = new Player(0, 0, "Player", 200, 50);
	m_ghost = new Ghost(0, 0, 200, 150, 0xFF6666FF, this);
	m_goal = new Actor(0, 0, "Goal");
	GameManager::getInstance()->init(m_ghost, m_goal);
	/*GameManager::m_fruitNum = 0;*/

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
		m_ghost->setTarget(m_fruitList[GameManager::m_fruitNum]);
		tile.actor = m_ghost;
		addActor(tile.actor);
		break;
	}
	case TileKey::FRUIT:
	{
		tile.cost = 1.0f;
		Fruit* fruit = new Fruit(position.x, position.y);
		tile.actor = fruit;
		m_fruitList.addItem(fruit);
		GameManager::getInstance()->setFruit(m_fruitList[GameManager::m_fruitNum]);
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