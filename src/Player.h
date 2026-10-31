#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <array>

class Player {
private:
	int playerX;
	int playerY;
	int playerSpeed;
	float playerCollisionRadius = 25.f;
	int playerHealth;
	bool isInvulnerable = false;
	bool damageAnimationVisible = false;
	sf::CircleShape shape;
	std::vector<Projectile> projectiles;
	sf::Clock fireClock;
	sf::Clock iFramesClock;
	sf::Clock damageAnimationClock;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	std::array<sf::IntRect, 4> animationFrames;
	std::size_t currentFrame = 0;
	sf::Clock animationClock;

public:
	Player();
	int getPlayerX();
	int getPlayerY();
	bool isDead();
	void takeDamage(float damage);
	float getPlayerCollisionRadius();
	void playerMoveLeft();
	void playerMoveRight();
	void playerMoveUp();
	void playerMoveDown();
	void draw(sf::RenderWindow& window);
	void shoot();
	void update();
	void reset();
	std::vector<Projectile>& getProjectiles();
	std::vector<Projectile>::iterator projectileRemoval(std::vector<Projectile>::iterator projectileIt);
};
