#pragma once
#include <vector>
#include "Enemy.h"
#include <SFML/Graphics.hpp>

class Player;
class ProjectileManager;

class EnemyManager {
private:
	sf::Texture enemyTexture;
	std::vector<Enemy> enemies;

public:
	EnemyManager();
	void spawnEnemy(float x, float y);
	void update(ProjectileManager& projectileManager);
	void draw(sf::RenderWindow& window);
	void checkCollisions(ProjectileManager& projectileManager);
	void checkPlayerCollision(Player& player);
	bool isEncounterFinished();
	void clearEnemies();
	void checkPlayerProjectileCollision(Player& player, ProjectileManager& projectileManager);
};