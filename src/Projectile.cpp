#include "Projectile.h"

Projectile::Projectile(float x, float y) {
	projectileX = x;
	projectileY = y;
	shape.setPosition(sf::Vector2f(projectileX, projectileY));
	projectileSpeed = 7;
	projectileDamage = 1;
	projectileRadius = 2.f;
	shape.setRadius(projectileRadius);
	shape.setFillColor(sf::Color::Red);
}

void Projectile::projectileMovement() {
	projectileX += projectileSpeed;
	shape.setPosition(sf::Vector2f(projectileX, projectileY));
}

void Projectile::draw(sf::RenderWindow& window) {
	window.draw(shape);
}

float Projectile::getProjectileX() {
	return projectileX;
}

float Projectile::getProjectileY() {
	return projectileY;
}

float Projectile::getProjectileRadius() {
	return projectileRadius;
}