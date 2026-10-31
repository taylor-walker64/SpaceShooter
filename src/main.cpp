#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Level.h"
#include <iostream>
#include <vector>
#include <cmath>

enum class GameState {
	MainMenu, Playing, GameOver
};

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Space Shooter");
	sf::Font gameFont;
	window.setFramerateLimit(60);
	if (!gameFont.openFromFile("assets/fonts/arial.ttf")) {
		std::cout << "Failed to load font!" << std::endl;
	}
	sf::Text gameOverText(gameFont, "GAME OVER", 48);
	sf::Text resetText(gameFont, "Press R to reset", 24);
	sf::FloatRect resetRect = resetText.getLocalBounds();
	sf::FloatRect gameOverRect = gameOverText.getLocalBounds();
	gameOverText.setOrigin((gameOverRect.size)/2.0f);
	gameOverText.setPosition({ 640.f, 360.f });
	resetText.setOrigin((resetRect.size / 2.0f));
	resetText.setPosition({ 640.f, 400.f });
	Player player;
	EnemyManager enemyManager;
	GameState currentState = GameState::Playing;
	Level level(1);

	level.startEncounter(enemyManager);
	
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) 
			{
				window.close();
			}
		}

		window.clear();

		if (currentState == GameState::Playing) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
			{
				player.shoot();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			{
				player.playerMoveLeft();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			{
				player.playerMoveRight();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			{
				player.playerMoveUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			{
				player.playerMoveDown();
			}

			player.update();
			enemyManager.update();
			enemyManager.checkCollisions(player);
			enemyManager.checkPlayerCollision(player);
			if (player.isDead()) {
				currentState = GameState::GameOver;
			}
			level.continueLevel(enemyManager);
			enemyManager.draw(window);
			player.draw(window);
		}

		if (currentState == GameState::GameOver)
		{
			window.draw(gameOverText);
			window.draw(resetText);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
				player.reset();
				enemyManager.clearEnemies();
				level.reset();
				level.startEncounter(enemyManager);
				currentState = GameState::Playing;
			}
		}

		window.display();
	}


}
