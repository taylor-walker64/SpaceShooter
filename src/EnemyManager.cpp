#include "EnemyManager.h"
#include "Player.h"
#include "AreCirclesOverlapping.h"
#include <vector>
#include <iostream>

void EnemyManager::spawnEnemy(float x, float y) {
	enemies.push_back(Enemy(x, y));
}

void EnemyManager::update() {
	for (auto it = enemies.begin(); it != enemies.end();)
	{
		it->update();
		++it;
	}
}

void EnemyManager::draw(sf::RenderWindow& window) {
	for (auto it = enemies.begin(); it != enemies.end(); ) {
		it->draw(window);
		++it;
	}
}

void EnemyManager::checkCollisions(Player& player) {
	for (auto projectileIt = player.getProjectiles().begin(); projectileIt != player.getProjectiles().end();)
	{
		bool projectileHit = false;
		for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
		{
			if (enemyIt->isHit(projectileIt->getProjectileX(), projectileIt->getProjectileY(), projectileIt->getProjectileRadius()))
			{
				enemyIt->takeDamage(1);
				projectileHit = true;
				projectileIt = player.projectileRemoval(projectileIt);
				if (enemyIt->isDead())
				{
					enemyIt = enemies.erase(enemyIt);
				}
				else
				{
					++enemyIt;
				}
				break;
			}
			else
			{
				++enemyIt;
			}
		}
		if (!projectileHit) {
			++projectileIt;
		}
	}
}

void EnemyManager::checkPlayerCollision(Player& player) {
	for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
	{
		if (AreCirclesOverlapping(player.getPlayerX(), player.getPlayerY(), player.getPlayerCollisionRadius(), enemyIt->getEnemyX(), enemyIt->getEnemyY(), enemyIt->getEnemyRadius())) {
			player.takeDamage(1);
			if (player.isDead()) {
				std::cout << "Player dead!" << std::endl;
			}
		}
		++enemyIt;
	}
}

bool EnemyManager::isEncounterFinished() {
	return enemies.empty();
}