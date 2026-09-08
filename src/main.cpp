#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Space Shooter");
	window.setFramerateLimit(60);

	Player player;
	EnemyManager enemyManager;

	enemyManager.spawnEnemy(1280, 0);
	
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) 
			{
				window.close();
			}
		}
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
		window.clear();
		enemyManager.draw(window);
		player.draw(window);
		window.display();

	}


}
