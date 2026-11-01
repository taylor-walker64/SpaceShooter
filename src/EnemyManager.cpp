#include "EnemyManager.h"
#include "Player.h"
#include "AreCirclesOverlapping.h"
#include "ProjectileManager.h"
#include <vector>
#include <iostream>
#include <stdexcept>

EnemyManager::EnemyManager() {
	if (!enemyTexture.loadFromFile("assets/sprites/enemydronespritesheet.png")) {
		throw std::runtime_error("Failed to load enemy drone texture");
	}
}

void EnemyManager::spawnEnemy(float x, float y) {
	enemies.push_back(Enemy(x, y, enemyTexture));
}

void EnemyManager::update(ProjectileManager& projectileManager) {
	for (auto it = enemies.begin(); it != enemies.end();) {
		it->update();
		it->updateAnimation();
		if (it->canFire()) {
			projectileManager.spawnProjectile(it->getEnemyX(), it->getEnemyY(), -1.0f, ProjectileOwner::Enemy);
		}
		++it;
	}
}

void EnemyManager::draw(sf::RenderWindow& window) {
	for (auto it = enemies.begin(); it != enemies.end(); ) {
		it->draw(window);
		++it;
	}
}

void EnemyManager::checkCollisions(ProjectileManager& projectileManager) {
	for (auto projectileIt = projectileManager.getProjectiles().begin(); projectileIt != projectileManager.getProjectiles().end();) {
		bool projectileHit = false;
		for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
			if (projectileIt->getProjectileOwner() == ProjectileOwner::Player && enemyIt->isHit(projectileIt->getProjectileX(), projectileIt->getProjectileY(), projectileIt->getProjectileRadius())) {
				enemyIt->takeDamage(1);
				projectileHit = true;
				projectileIt = projectileManager.projectileRemoval(projectileIt);
				if (enemyIt->isDead()) {
					enemyIt = enemies.erase(enemyIt);
				}
				else {
					++enemyIt;
				}
				break;
			}
			else {
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

void EnemyManager::checkPlayerProjectileCollision(Player& player, ProjectileManager& projectileManager) {
	for (auto projectileIt = projectileManager.getProjectiles().begin(); projectileIt != projectileManager.getProjectiles().end();) {
		if (projectileIt->getProjectileOwner() == ProjectileOwner::Enemy && AreCirclesOverlapping(player.getPlayerX(), player.getPlayerY(), player.getPlayerCollisionRadius(), projectileIt->getProjectileX(), projectileIt->getProjectileY(), projectileIt->getProjectileRadius())) {
			player.takeDamage(1);
			projectileIt = projectileManager.projectileRemoval(projectileIt);
		}
		else {
			++projectileIt;
		}
	}
}

bool EnemyManager::isEncounterFinished() {
	return enemies.empty();
}

void EnemyManager::clearEnemies() {
	enemies.clear();
}