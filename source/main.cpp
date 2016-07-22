#include <iostream>

#include "game.hpp"
#include "config.h"

int main(int argc, const char* argv[]) {
	std::cout << "Running version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;
	
    try {
        return Game(argc, argv).run();
    }
    catch(std::exception& e) {
        std::cerr << "Exception thrown: " << e.what() << std::endl;
        std::cerr << "Exiting..." << std::endl;
        return 1;
    }
    catch(...) {
        std::cerr << "Unknown exception occured" << std::endl;
        return 1;
    }
}

