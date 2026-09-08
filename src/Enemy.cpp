#include "Enemy.h"
#include "checkCollision.h"

Enemy::Enemy(float x, float y) {
	enemyX = x;
	enemyY = y;
	enemySpeed = 1;
	enemyRadius = 10.f;
	enemyHealth = 1;
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(sf::Vector2f(enemyX, enemyY));
	shape.setRadius(enemyRadius);
}

void Enemy::draw(sf::RenderWindow& window) {
	window.draw(shape);
}

void Enemy::update() {
	enemyX -= enemySpeed;
	shape.setPosition(sf::Vector2f(enemyX, enemyY));
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
	return checkCollision(projectileX, projectileY, projectileRadius, enemyX, enemyY, enemyRadius);
}

void Enemy::takeDamage(float damage) {
	enemyHealth -= damage;
}

bool Enemy::isDead() {
	return enemyHealth <= 0;
}