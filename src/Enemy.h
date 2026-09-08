#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
private:
	float enemyX;
	float enemyY;
	float enemySpeed;
	float enemyRadius;
	float enemyHealth;
	sf::CircleShape shape;

public:
	Enemy(float x, float y);
	void draw(sf::RenderWindow& window);
	void update();
	float getEnemyX();
	float getEnemyY();
	float getEnemyRadius();
	bool isHit(float projectileX, float projectileY, float projectileRadius);
	void takeDamage(float damage);
	bool isDead();
};