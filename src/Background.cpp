#include "Background.h"

Background::Background()
	: texture("assets/backgrounds/backgroundv2.png"),
	sprite(texture) { }

void Background::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}