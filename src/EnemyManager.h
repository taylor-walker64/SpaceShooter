#pragma once
#include <vector>
#include "Enemy.h"

class Player;

class EnemyManager {
private:
	std::vector<Enemy> enemies;

public:
	void spawnEnemy(float x, float y);
	void update();
	void draw(sf::RenderWindow& window);
	void checkCollisions(Player& player);
};