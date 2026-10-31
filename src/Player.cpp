#include "Player.h"
#include <iostream>

Player::Player() 
	: playerTexture("../../../../assets/playerspritesheet.png"),
	  playerSprite(playerTexture)
{
	playerX = 100;
	playerY = 350;
	playerSpeed = 6;
	playerHealth = 3;
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::Green);
	playerSprite.setScale({2.0f, 2.0f});
	playerSprite.setOrigin({32.f, 32.f});
	playerSprite.setPosition(sf::Vector2f(playerX, playerY));
	animationFrames = {
	sf::IntRect({0, 0}, {64, 64}),
	sf::IntRect({64, 0}, {64, 64}),
	sf::IntRect({0, 64}, {64, 64}),
	sf::IntRect({64, 64}, {64, 64})
	};
	playerSprite.setTextureRect(animationFrames[0]);
}

int Player::getPlayerX() {
	return playerX;
}

int Player::getPlayerY() {
	return playerY;
}

float Player::getPlayerCollisionRadius() {
	return playerCollisionRadius;
}

void Player::playerMoveLeft() {
	sf::FloatRect bounds = playerSprite.getGlobalBounds();
	if (bounds.position.x - playerSpeed >= 0) {
		playerX -= playerSpeed;
	}
	playerSprite.setPosition(sf::Vector2f(playerX, playerY));
}

void Player::playerMoveRight() {
	sf::FloatRect bounds = playerSprite.getGlobalBounds();
	if (bounds.position.x + playerSpeed <= 1190) {
		playerX += playerSpeed;
	}
	playerSprite.setPosition(sf::Vector2f(playerX, playerY));
}

void Player::playerMoveUp() {
	sf::FloatRect bounds = playerSprite.getGlobalBounds();
	if (bounds.position.y - playerSpeed >= 0) {
		playerY -= playerSpeed;
	}
	playerSprite.setPosition(sf::Vector2f(playerX, playerY));
}

void Player::playerMoveDown() {
	sf::FloatRect bounds = playerSprite.getGlobalBounds();
	if (bounds.position.y + playerSpeed <= 660) {
		playerY += playerSpeed;
	}
	playerSprite.setPosition(sf::Vector2f(playerX, playerY));
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(playerSprite);

	// Debug sprite boundary box: remove later
	//sf::CircleShape debugHitbox(playerCollisionRadius);
	//debugHitbox.setOrigin({ playerCollisionRadius, playerCollisionRadius });
	//debugHitbox.setPosition({ static_cast<float>(playerX),
	//						 static_cast<float>(playerY) });
	//debugHitbox.setFillColor(sf::Color::Transparent);
	//debugHitbox.setOutlineColor(sf::Color::Red);
	//debugHitbox.setOutlineThickness(2.f);
	//window.draw(debugHitbox);
	// End debug box

	for (Projectile& projectile : projectiles) {
		projectile.draw(window);
	}
}

void Player::shoot() {
	if (fireClock.getElapsedTime().asSeconds() >= 0.25f) {
		projectiles.push_back(Projectile(playerX + 40, playerY));
		fireClock.restart();
	}
	
}

void Player::update() {
	if (animationClock.getElapsedTime().asMilliseconds() >= 100) {
		currentFrame++;
		if (currentFrame >= animationFrames.size()) {
			currentFrame = 0;
		}
		playerSprite.setTextureRect(animationFrames[currentFrame]);
		animationClock.restart();
	}
	for (auto it = projectiles.begin(); it != projectiles.end();) {
		it->projectileMovement();
		if (it->getProjectileX() > 1280) {
			it = projectiles.erase(it);
		}
		else ++it;
	}
	if (isInvulnerable && iFramesClock.getElapsedTime().asSeconds() >= 1.00f) {
		isInvulnerable = false;
		damageAnimationVisible = false;
		playerSprite.setColor(sf::Color::White);
	}
	if (isInvulnerable && damageAnimationClock.getElapsedTime().asMilliseconds() >= 100) {
		damageAnimationVisible = !damageAnimationVisible;
		if (!damageAnimationVisible) {
			playerSprite.setColor(sf::Color(255, 255, 255, 100));
		}
		else {
			playerSprite.setColor(sf::Color::White);
		}
		damageAnimationClock.restart();
	}
}

std::vector<Projectile>& Player::getProjectiles() {
	return projectiles;
}

std::vector<Projectile>::iterator Player::projectileRemoval(std::vector<Projectile>::iterator projectileIt) {
	return projectiles.erase(projectileIt);
}

bool Player::isDead() {
	return playerHealth <= 0;
}

void Player::takeDamage(float damage) {
	if (!isInvulnerable) {
		playerHealth -= damage;
		isInvulnerable = true;
		iFramesClock.restart();
		damageAnimationClock.restart();
	}
}

void Player::reset() {
	playerX = 100;
	playerY = 350;
	playerHealth = 3;
	isInvulnerable = false;
	damageAnimationVisible = false;
	iFramesClock.restart();
	damageAnimationClock.restart();
	projectiles.clear();
	playerSprite.setPosition(sf::Vector2f(playerX, playerY));
	currentFrame = 0;
	animationClock.restart();
	playerSprite.setTextureRect(animationFrames[currentFrame]);
	playerSprite.setColor(sf::Color::White);
}