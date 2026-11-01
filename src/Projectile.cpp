#include "Projectile.h"

Projectile::Projectile(float x, float y, float direction, ProjectileOwner owner, const sf::Texture& texture) : sprite(texture) {
	projectileX = x;
	projectileY = y;
	projectileDirection = direction;
	sprite.setPosition(sf::Vector2f(projectileX, projectileY));
	projectileSpeed = 7;
	projectileDamage = 1;
	projectileRadius = 3.f;
	projectileOwner = owner;
	sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 64, 64 }));
	if (projectileOwner == ProjectileOwner::Enemy)
	{
		sprite.setColor(sf::Color::Cyan);
	}
	sprite.setOrigin({ 32.f, 32.f });
}

void Projectile::projectileMovement() {
	projectileX += projectileSpeed * projectileDirection;
	sprite.setPosition(sf::Vector2f(projectileX, projectileY));
}

void Projectile::draw(sf::RenderWindow& window) {
	window.draw(sprite);
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

ProjectileOwner Projectile::getProjectileOwner() {
	return projectileOwner;
}

void Projectile::updateAnimation() {
	if (animationClock.getElapsedTime().asSeconds() >= 0.1f) {
		currentFrame = (currentFrame + 1) % 2;
		sprite.setTextureRect(
			sf::IntRect({ 0, currentFrame * 64 }, { 64, 64 }));
		animationClock.restart();
	}
}

