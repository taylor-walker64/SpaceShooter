#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Projectile.h"
#include "Enemy.h"
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Space Shooter");
	window.setFramerateLimit(60);

	Player player;

	std::vector<Enemy> enemies;

	enemies.push_back(Enemy(1280, 50));
	enemies.push_back(Enemy(1280, 100));
	enemies.push_back(Enemy(1280, 150));
	enemies.push_back(Enemy(1280, 200));
	enemies.push_back(Enemy(1280, 250));
	enemies.push_back(Enemy(1280, 300));
	enemies.push_back(Enemy(1280, 350));
	enemies.push_back(Enemy(1280, 400));
	enemies.push_back(Enemy(1280, 450));
	enemies.push_back(Enemy(1280, 500));
	enemies.push_back(Enemy(1280, 550));
	enemies.push_back(Enemy(1280, 600));
	enemies.push_back(Enemy(1280, 650));
	enemies.push_back(Enemy(1280, 700));

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>()) 
			{
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift))
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
		for (auto it = enemies.begin(); it != enemies.end();)	
		{
			it->update();
			++it;
		}

		for (auto projectileIt = player.getProjectiles().begin(); projectileIt != player.getProjectiles().end();)
		{
			bool projectileHit = false;
			for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();)
			{
				if (enemyIt->isHit(projectileIt->getProjectileX(), projectileIt->getProjectileY(), projectileIt->getProjectileRadius())) 
				{
					enemyIt->takeDamage(1);
					projectileHit = true;
					projectileIt = player.projectileRemoval(projectileIt);
					if (enemyIt->isDead()) 
					{
						enemyIt = enemies.erase(enemyIt);
					}
					else
					{
						++enemyIt;
					}
					break;
				}
				else
				{
					++enemyIt;
				}
			}
			if (!projectileHit) {
				++projectileIt;
			}
		}

		window.clear();
		for (auto it = enemies.begin(); it != enemies.end(); ) {
			it->draw(window);
			++it;
		}
		player.draw(window);
		window.display();

	}


}
