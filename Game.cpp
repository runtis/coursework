#include "Game.h"
#include "Direction.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

Game* Game::instance = nullptr;

Game::Game() : isRunning(false), score(0), width(30), height(15) {}

Game* Game::getInstance() {
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}

void Game::initialize() {
    isRunning = true;
    score = 0;
    food.respawn(width, height, snake.getBody());

    // Настраиваем консоль для уменьшения мерцания
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Скрываем курсор
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Game::run() {
    while (isRunning) {
        processInput();
        update();
        checkCollisions();
        render();
        Sleep(150);
    }
}

void Game::processInput() {
    if (_kbhit()) {
        int key = _getch();

        if (key == 'x' || key == 'X' || key == 215 || key == 135) {
            isRunning = false;
            return;
        }

        switch (key) {
        case 'w': case 'W': case 230: case 150:
            snake.changeDirection(Direction::UP);
            break;
        case 's': case 'S': case 235: case 155:
            snake.changeDirection(Direction::DOWN);
            break;
        case 'a': case 'A': case 228: case 148:
            snake.changeDirection(Direction::LEFT);
            break;
        case 'd': case 'D': case 162: case 130:
            snake.changeDirection(Direction::RIGHT);
            break;
        case 224:
            int arrow = _getch();
            switch (arrow) {
            case 72: snake.changeDirection(Direction::UP); break;
            case 80: snake.changeDirection(Direction::DOWN); break;
            case 75: snake.changeDirection(Direction::LEFT); break;
            case 77: snake.changeDirection(Direction::RIGHT); break;
            }
            break;
        }
    }
}

void Game::update() {
    snake.update();
}

void Game::render() {
    // Вместо system("cls") используем установку курсора в начало
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = { 0, 0 };
    SetConsoleCursorPosition(hConsole, coordScreen);

    // Создаем буфер для отрисовки
    std::string buffer;
    buffer.reserve((width + 3) * (height + 5)); // Резервируем память

    // Верхняя строка с информацией
    buffer += "=== Змейка === Счет: " + std::to_string(score) + "\n";

    // Верхняя граница
    buffer += std::string(width + 2, '#') + "\n";

    // Игровое поле
    for (int y = 0; y < height; y++) {
        buffer += "#";
        for (int x = 0; x < width; x++) {
            Position currentPos(x, y);
            const auto& body = snake.getBody();

            if (!body.empty() && body[0] == currentPos) {
                buffer += "@"; // Голова
            }
            else {
                bool isBodyPart = false;
                for (size_t i = 1; i < body.size(); i++) {
                    if (body[i] == currentPos) {
                        buffer += "o"; // Тело
                        isBodyPart = true;
                        break;
                    }
                }

                if (!isBodyPart) {
                    if (food.getPosition() == currentPos) {
                        buffer += "&"; // Еда
                    }
                    else {
                        buffer += " "; // Пустота
                    }
                }
            }
        }
        buffer += "#\n";
    }

    // Нижняя граница
    buffer += std::string(width + 2, '#') + "\n";

    // Управление
    buffer += "Управление: WASD/стрелки, X - выход\n";

    // Выводим весь буфер за один раз
    std::cout << buffer;
}

void Game::checkCollisions() {
    const auto& head = snake.getBody()[0];

    if (head == food.getPosition()) {
        score += 10;
        snake.grow();
        food.respawn(width, height, snake.getBody());
    }

    if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height ||
        snake.checkSelfCollision()) {
        gameOver();
    }
}

void Game::gameOver() {
    isRunning = false;
    // Показываем курсор обратно
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

}

bool Game::getIsRunning() const {
    return isRunning;
}