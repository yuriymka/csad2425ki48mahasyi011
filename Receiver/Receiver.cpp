#include <iostream>
#include <windows.h>
#include "SerialPort.hpp"

/// @brief Ім'я COM-порту для зв'язку з Arduino.
char portName[] = "\\\\.\\COM3";

/// @brief Вказівник на об'єкт серійного порту.
SerialPort* arduino;

/// @brief Початковий стан дошки (порожні клітинки позначені пробілами).
std::string board = "         ";

/// @brief Виводить ігрову дошку в консоль.
void displayBoard() {
    std::cout << "\n";
    for (int i = 0; i < 9; i++) {
        std::cout << " " << (board[i] == ' ' ? ' ' : board[i]) << " ";
        if (i % 3 != 2) std::cout << "|";
        if (i % 3 == 2 && i != 8) std::cout << "\n---+---+---\n";
    }
    std::cout << "\n\n";
}

/// @brief Скидає стан ігрової дошки до початкового значення.
void resetBoard() {
    board = "         ";
    displayBoard();
}

/// @brief Ініціалізує підключення до Arduino через серійний порт.
void setup() {
    arduino = new SerialPort(portName);

    if (arduino->isConnected()) {
        std::cout << "Connection established on " << portName << std::endl;
    } else {
        std::cout << "Error connecting to " << portName << std::endl;
    }
}

/// @brief Основний цикл обробки даних з Arduino.
void loop() {
    if (arduino->isConnected()) {
        char incomingData[256] = ""; ///< Буфер для отриманих даних.
        int readResult = arduino->readSerialPort(incomingData, 255);

        if (readResult > 0) {
            std::cout << "Received: " << incomingData << std::endl;

            // Оновлення стану дошки
            if (incomingData[0] == 'X' || incomingData[0] == 'O') {
                char player = incomingData[0];
                int position = incomingData[2] - '1';

                if (board[position] == ' ') {
                    board[position] = player;
                    displayBoard();
                }
            }

            // Перевірка завершення гри
            if (strstr(incomingData, "Y 1")) {
                std::cout << "Player X wins!" << std::endl;
            } else if (strstr(incomingData, "Y 2")) {
                std::cout << "Player O wins!" << std::endl;
            } else if (strstr(incomingData, "Y 3")) {
                std::cout << "It's a draw!" << std::endl;
            } else if (strstr(incomingData, "G 0")) {
                std::cout << "Game Reset" << std::endl;
                resetBoard();
            }
        }
    }
}

/// @brief Точка входу програми.
/// @return Код завершення.
int main() {
    setup();
    while (true) {
        loop();
    }
    return 0;
}
