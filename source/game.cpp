#include "game.hpp"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Game::Game(int argc, const char* argv[]) :
	window()
{
}

Game::~Game() {
}

int Game::run() {
	// Create a window
	window.create(sf::VideoMode(800, 600), "Skeleton", sf::Style::Titlebar | sf::Style::Close);

	sf::Clock clock;

	bool done = false;
	while(!done)
	{
		// Handle events
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed ||
			  (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
				done = true;
				continue;
			}

			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				window.setSize({800,600});
			}
		}
	}

	// Application has finished running
	window.close();

	return 0;
}

