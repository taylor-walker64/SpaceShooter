#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
private:
	float enemyX;
	float enemyY;
	float enemySpeed;
	float enemyRadius;
	float enemyHealth;
	sf::Sprite sprite;
	sf::Clock fireClock;
	float firingCooldown;
	sf::Clock animationClock;
	int currentFrame = 0;

public:
	Enemy(float x, float y, const sf::Texture& texture);
	void draw(sf::RenderWindow& window);
	void update();
	float getEnemyX();
	float getEnemyY();
	float getEnemyRadius();
	bool isHit(float projectileX, float projectileY, float projectileRadius);
	void takeDamage(float damage);
	bool isDead();
	bool canFire();
	void updateAnimation();
};