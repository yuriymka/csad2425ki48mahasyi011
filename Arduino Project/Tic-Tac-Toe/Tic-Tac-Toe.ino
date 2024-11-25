#include <Keypad.h>

// Піни для рядків і стовпців
const int rowPins[4] = {2, 3, 4, 5};
const int colPins[4] = {6, 7, 8, 9};

// Таблиця відповідності клавіш
char keyMap[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Буфер для зберігання останньої натиснутої клавіші
char lastKey = '\0';
char currentPlayer = 'X'; // Починає X
int gameMode = 0; // 1 - AI проти Arduino, 2 - стандартний

// Ігрове поле
char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };

void resetGame() {
    board[0][0] = '1'; board[0][1] = '2'; board[0][2] = '3';
    board[1][0] = '4'; board[1][1] = '5'; board[1][2] = '6';
    board[2][0] = '7'; board[2][1] = '8'; board[2][2] = '9';
    currentPlayer = 'X';
    Serial.println("G 0");
}

int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return (board[i][0] == 'X') ? 1 : 2;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return (board[0][i] == 'X') ? 1 : 2;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return (board[0][0] == 'X') ? 1 : 2;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return (board[0][2] == 'X') ? 1 : 2;
    }
    bool full = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                full = false;
            }
        }
    }
    if (full) return 3;
    return 0;
}

// Сканує кнопкову матрицю і повертає натиснуту клавішу
char scanKeypad() {
    for (int row = 0; row < 4; row++) {
        digitalWrite(rowPins[row], LOW); // Активуємо рядок
        for (int col = 0; col < 4; col++) {
            if (digitalRead(colPins[col]) == LOW) { // Якщо кнопка натиснута
                digitalWrite(rowPins[row], HIGH); // Вимикаємо рядок
                return keyMap[row][col]; // Повертаємо відповідний символ
            }
        }
        digitalWrite(rowPins[row], HIGH); // Вимикаємо рядок
    }
    return '\0'; // Якщо клавіша не натиснута
}

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 4; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH);
        pinMode(colPins[i], INPUT_PULLUP);
    }
}

void loop() {
    char pressedKey = scanKeypad(); // Сканування кнопок
    if (pressedKey != '\0' && pressedKey != lastKey) { // Якщо натиснута нова клавіша
        lastKey = pressedKey;
        if (pressedKey == '#') {
            gameMode = 1;
            Serial.println("M 1");
            resetGame();
        }
        else if (pressedKey == '0') {
            gameMode = 2;
            Serial.println("M 2");
            resetGame();
        }
    } else if (pressedKey == '\0') {
        lastKey = '\0'; // Скидання, якщо клавіша відпущена
    }
}
