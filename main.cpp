#include "Game.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "RU");
    Game* game = Game::getInstance();

    game->initialize();
    game->run();

    std::cout << "���� ��������. ������� �� ����!\n";
    system("pause");
    return 0;
}