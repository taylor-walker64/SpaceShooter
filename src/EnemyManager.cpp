#include "EnemyManager.h"
#include "Player.h"
#include <vector>

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