/// @brief Масив пінів для рядків матриці.
const int rowPins[4] = { 2, 3, 4, 5 };

/// @brief Масив пінів для стовпців матриці.
const int colPins[4] = { 6, 7, 8, 9 };

/// @brief Таблиця відповідності клавіш для кнопкової матриці.
char keyMap[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

/// @brief Остання натиснута клавіша.
char lastKey = '\0';

/// @brief Поточний гравець ('X' чи 'O').
char currentPlayer = 'X';

/// @brief Ігрове поле.
char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };

/// @brief Перевіряє стан гри на виграш або нічию.
/// @return 1 - виграв X, 2 - виграв O, 3 - нічия, 0 - гра триває.
int checkWin() {
    // Горизонталі
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return (board[i][0] == 'X') ? 1 : 2;
        }
    }

    // Вертикалі
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return (board[0][i] == 'X') ? 1 : 2;
        }
    }

    // Діагоналі
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return (board[0][0] == 'X') ? 1 : 2;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return (board[0][2] == 'X') ? 1 : 2;
    }

    // Нічия
    bool full = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                full = false;
            }
        }
    }
    return full ? 3 : 0;
}

/// @brief Скидає гру до початкового стану.
void resetGame() {
    board[0][0] = '1'; board[0][1] = '2'; board[0][2] = '3';
    board[1][0] = '4'; board[1][1] = '5'; board[1][2] = '6';
    board[2][0] = '7'; board[2][1] = '8'; board[2][2] = '9';
    currentPlayer = 'X';
    Serial.println("G 0");
}

/// @brief Ініціалізація кнопкової матриці та серійного зв'язку.
void setup() {
    for (int i = 0; i < 4; i++) {
        pinMode(rowPins[i], OUTPUT);
        digitalWrite(rowPins[i], HIGH);
        pinMode(colPins[i], INPUT_PULLUP);
    }
    Serial.begin(9600);
}

/// @brief Основний цикл обробки натискань клавіш.
void loop() {
    char pressedKey = scanKeypad();
    if (pressedKey != '\0' && pressedKey != lastKey) {
        lastKey = pressedKey;
        if (pressedKey >= '1' && pressedKey <= '9') {
            int row = (pressedKey - '1') / 3;
            int col = (pressedKey - '1') % 3;
            if (board[row][col] != 'X' && board[row][col] != 'O') {
                board[row][col] = currentPlayer;
                Serial.print(currentPlayer);
                Serial.print(" ");
                Serial.println(pressedKey);
                int result = checkWin();
                if (result > 0) {
                    Serial.println(result == 1 ? "Y 1" : result == 2 ? "Y 2" : "Y 3");
                }
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }
        else if (pressedKey == 'D') {
            resetGame();
        }
    }
    else if (pressedKey == '\0') {
        lastKey = '\0';
    }
    delay(50);
}

/// @brief Сканує кнопкову матрицю.
/// @return Символ натиснутої клавіші або '\0', якщо не натиснуто.
char scanKeypad() {
    for (int row = 0; row < 4; row++) {
        digitalWrite(rowPins[row], LOW);
        for (int col = 0; col < 4; col++) {
            if (digitalRead(colPins[col]) == LOW) {
                digitalWrite(rowPins[row], HIGH);
                return keyMap[row][col];
            }
        }
        digitalWrite(rowPins[row], HIGH);
    }
    return '\0';
}
