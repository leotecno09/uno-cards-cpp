#include <iostream>
#include "include/Game.h"


int main() {
    std::unique_ptr<Game> game = std::make_unique<Game>();

#ifdef _WIN32
    game->setWindows();
#endif

    game->play();
}
