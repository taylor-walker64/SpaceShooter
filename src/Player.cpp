#include "Player.h"
#include <iostream>

Player::Player() {
	playerX = 0;
	playerY = 0;
	playerSpeed = 3;
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::Green);
}

int Player::getPlayerX() {
	return playerX;
}

int Player::getPlayerY() {
	return playerY;
}

void Player::playerMoveLeft() {
	if (playerX - playerSpeed >= 0) {
		playerX -= playerSpeed;
	}
	shape.setPosition(sf::Vector2f(playerX, playerY));
}

void Player::playerMoveRight() {
	if (playerX + playerSpeed <= 1000) {
		playerX += playerSpeed;
	}
	shape.setPosition(sf::Vector2f(playerX, playerY));
}

void Player::playerMoveUp() {
	if (playerY - playerSpeed >= 0) {
		playerY -= playerSpeed;
	}
	shape.setPosition(sf::Vector2f(playerX, playerY));
}

void Player::playerMoveDown() {
	if (playerY + playerSpeed <= 700) {
		playerY += playerSpeed;
	}
	shape.setPosition(sf::Vector2f(playerX, playerY));
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(shape);
	for (Projectile& projectile : projectiles) {
		projectile.draw(window);
	}
}

void Player::shoot() {
	if (fireClock.getElapsedTime().asSeconds() >= 0.25f) {
		projectiles.push_back(Projectile(playerX, playerY + 5));
		fireClock.restart();
	}
	
}

void Player::update() {
	for (auto it = projectiles.begin(); it != projectiles.end();) {
		it->projectileMovement();
		if (it->getProjectileX() > 1280) {
			it = projectiles.erase(it);
		}
		else ++it;
	}
}

std::vector<Projectile>& Player::getProjectiles() {
	return projectiles;
}

std::vector<Projectile>::iterator Player::projectileRemoval(std::vector<Projectile>::iterator projectileIt) {
	return projectiles.erase(projectileIt);
}