#pragma once
#include <vector>
#include "Projectile.h"

class ProjectileManager {
private:
	sf::Texture projectileTexture;
	std::vector<Projectile> projectiles;

public:
	ProjectileManager();
	void spawnProjectile(float x, float y, float direction, ProjectileOwner owner);
	void update();
	void draw(sf::RenderWindow& window);
	std::vector<Projectile>::iterator projectileRemoval(std::vector<Projectile>::iterator projectileIt);
	std::vector<Projectile>& getProjectiles();
	void clearProjectiles();
};