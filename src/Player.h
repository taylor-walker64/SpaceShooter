#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <vector>

class Player {
private:
	int playerX;
	int playerY;
	int playerSpeed;
	sf::CircleShape shape;
	std::vector<Projectile> projectiles;
	sf::Clock fireClock;

public:
	Player();
	int getPlayerX();
	int getPlayerY();
	void playerMoveLeft();
	void playerMoveRight();
	void playerMoveUp();
	void playerMoveDown();
	void draw(sf::RenderWindow& window);
	void shoot();
	void update();
	std::vector<Projectile>& getProjectiles();
	std::vector<Projectile>::iterator projectileRemoval(std::vector<Projectile>::iterator projectileIt);
};
