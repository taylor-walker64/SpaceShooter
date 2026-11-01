#pragma once
#include <SFML/Graphics.hpp>

enum class ProjectileOwner {
	Player = 0, Enemy = 1
};

class Projectile {
private:
	float projectileX;
	float projectileY;
	float projectileRadius;
	float projectileSpeed;
	float projectileDirection;
	int projectileDamage;
	sf::Sprite sprite;
	ProjectileOwner projectileOwner;
	sf::Clock animationClock;
	int currentFrame = 0;

public:
	Projectile(float x, float y, float direction, ProjectileOwner owner, const sf::Texture& texture);
	float getProjectileX();
	float getProjectileY();
	float getProjectileRadius();
	int getProjectileSpeed();
	int getProjectileDamage();
	void draw(sf::RenderWindow& window);
	void projectileMovement();
	ProjectileOwner getProjectileOwner();
	void updateAnimation();
};
