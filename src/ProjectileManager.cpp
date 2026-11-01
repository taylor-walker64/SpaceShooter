#pragma once
#include "ProjectileManager.h"
#include <stdexcept>

ProjectileManager::ProjectileManager() {
	if (!projectileTexture.loadFromFile("assets/sprites/playerkineticprojectile.png"))
	{
		throw std::runtime_error("Failed to load player projectile texture");
	}
}

void ProjectileManager::spawnProjectile(float x, float y, float direction, ProjectileOwner owner) {
	projectiles.push_back(Projectile(x, y, direction, owner, projectileTexture));
}

void ProjectileManager::update() {
	for (auto it = projectiles.begin(); it != projectiles.end();) {
		it->projectileMovement();
		it->updateAnimation();
		if (it->getProjectileX() > 1280 || it->getProjectileX() < 0) {
			it = projectiles.erase(it);
		}
		else ++it;
	}
}

void ProjectileManager::draw(sf::RenderWindow& window) {
	for (Projectile& projectile : projectiles) {
		projectile.draw(window);
	}
}

std::vector<Projectile>::iterator ProjectileManager::projectileRemoval(std::vector<Projectile>::iterator projectileIt) {
	return projectiles.erase(projectileIt);
}

std::vector<Projectile>& ProjectileManager::getProjectiles() {
	return projectiles;
}

void ProjectileManager::clearProjectiles() {
	projectiles.clear();
}