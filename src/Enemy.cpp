#include "Enemy.h"
#include "AreCirclesOverlapping.h"

Enemy::Enemy(float x, float y, const sf::Texture& texture) : sprite(texture) {
	enemyX = x;
	enemyY = y;
	enemySpeed = 1;
	enemyRadius = 15.f;
	enemyHealth = 1;
	firingCooldown = 2.0f;
	sprite.setPosition(sf::Vector2f(enemyX, enemyY));
	sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 64, 64 }));
	sprite.setOrigin({ 32.f, 32.f });
}

void Enemy::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Enemy::update() {
	enemyX -= enemySpeed;
	sprite.setPosition(sf::Vector2f(enemyX, enemyY));
}

float Enemy::getEnemyX() {
	return enemyX;
}

float Enemy::getEnemyY() {
	return enemyY;
}

float Enemy::getEnemyRadius() {
	return enemyRadius;
}

bool Enemy::isHit(float projectileX, float projectileY, float projectileRadius) {
	return AreCirclesOverlapping(projectileX, projectileY, projectileRadius, enemyX, enemyY, enemyRadius);
}

void Enemy::takeDamage(float damage) {
	enemyHealth -= damage;
}

bool Enemy::isDead() {
	return enemyHealth <= 0;
}

bool Enemy::canFire() {
	if ((fireClock.getElapsedTime().asSeconds() >= firingCooldown)) {
		fireClock.restart();
		return true;
	}
	else {
		return false;
	}
}

void Enemy::updateAnimation() {
	if (animationClock.getElapsedTime().asSeconds() >= 0.15f) {
		currentFrame = (currentFrame + 1) % 4;
		sprite.setTextureRect(sf::IntRect({ (currentFrame % 2) * 64, (currentFrame / 2) * 64 }, { 64, 64 }));
		animationClock.restart();
	}
}