#ifndef _MAIN__GAME_HPP_
#define _MAIN__GAME_HPP_

#include <memory>

#include <SFML/Window.hpp>

class Game {
private:
	sf::Window window;

	~Game();
	Game(int argc, const char* argv[]);

	int run();

	friend int main(int, const char**);
};

#endif
