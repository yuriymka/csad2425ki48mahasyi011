#include <iostream>
#include <windows.h>
#include "SerialPort.hpp"

char portName[] = "\\\\.\\COM3"; // Задайте ваш COM-порт (перевірте у диспетчері пристроїв)
SerialPort* arduino;

// Початковий стан дошки (порожні клітинки позначені пробілами)
std::string board = "         "; // Клітинки порожні

void displayBoard() {
    // Виведення дошки в консоль
    std::cout << "\n";
    for (int i = 0; i < 9; i++) {
        std::cout << " " << (board[i] == ' ' ? ' ' : board[i]) << " "; // Показуємо або 'X', або 'O'
        if (i % 3 != 2) std::cout << "|";
        if (i % 3 == 2 && i != 8) std::cout << "\n---+---+---\n";
    }
    std::cout << "\n\n";
}

void resetBoard() {
    // Очищаємо дошку
    board = "         "; // Відновлюємо порожній початковий стан
    displayBoard(); // Оновлюємо виведення дошки на екран
}

void setup() {
    arduino = new SerialPort(portName);

    if (arduino->isConnected()) {
        std::cout << "Connection established on " << portName << std::endl;
    }
    else {
        std::cout << "Error connecting to " << portName << std::endl;
    }
}

void loop() {
    if (arduino->isConnected()) {
        char incomingData[256] = ""; // Буфер для отриманих даних
        int readResult = arduino->readSerialPort(incomingData, 255);

        if (readResult > 0) {
            std::cout << "Received: " << incomingData << std::endl;

            // Обробка повідомлення для оновлення дошки
            if (incomingData[0] == 'X' || incomingData[0] == 'O') {
                // Формат повідомлення: X 1 або O 2
                char player = incomingData[0];
                int position = incomingData[2] - '1'; // Отримуємо позицію з цифри (1-9)

                // Оновлення дошки
                if (board[position] == ' ') { // Якщо клітинка порожня
                    board[position] = player;
                    displayBoard();
                }
            }

            // Перевірка на виграш
            if (strstr(incomingData, "Y 1")) {
                std::cout << "Player X wins!" << std::endl; // Виграв X
            }
            else if (strstr(incomingData, "Y 2")) {
                std::cout << "Player O wins!" << std::endl; // Виграв O
            }
            else if (strstr(incomingData, "Y 3")) {
                std::cout << "It's a draw!" << std::endl; // Нічия
            }
            else if (strstr(incomingData, "G 0")) {
                std::cout << "Game Reset" << std::endl; // Нічия
                resetBoard(); // Очищаємо дошку після скидання гри
            }
        }
    }
}

int main() {
    setup();
    while (true) {
        loop();
    }
    return 0;
}
