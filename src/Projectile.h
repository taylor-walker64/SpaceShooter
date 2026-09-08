#pragma once
#include <SFML/Graphics.hpp>

class Projectile {
private:
	float projectileX;
	float projectileY;
	float projectileRadius;
	float projectileSpeed;
	int projectileDamage;
	sf::CircleShape shape;

public:
	Projectile(float x, float y);
	float getProjectileX();
	float getProjectileY();
	float getProjectileRadius();
	int getProjectileSpeed();
	int getProjectileDamage();
	void draw(sf::RenderWindow& window);
	void projectileMovement();
};
