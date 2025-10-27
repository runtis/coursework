#include "Game.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "RU");
    Game* game = Game::getInstance();

    game->initialize();
    game->run();

    std::cout << "Игра окончена. Спасибо за игру!\n";
    system("pause");
    return 0;
}