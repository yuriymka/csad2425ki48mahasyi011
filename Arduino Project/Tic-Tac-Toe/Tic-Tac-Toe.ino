// Піни для рядків і стовпців
const int rowPins[4] = {2, 3, 4, 5}; // Рядки
const int colPins[4] = {6, 7, 8, 9}; // Стовпці

// Таблиця відповідності клавіш
char keyMap[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Буфер для зберігання останньої натиснутої клавіші
char lastKey = '\0';

// Змінна для зберігання поточного ходу (X або O)
char currentPlayer = 'X'; // Починає X

// Ігрове поле
char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };

// Функція для перевірки виграшу
int checkWin() {
  // Перевірка горизонталей
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
      return (board[i][0] == 'X') ? 1 : 2; // X виграв (1) або O виграв (2)
    }
  }

  // Перевірка вертикалей
  for (int i = 0; i < 3; i++) {
    if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
      return (board[0][i] == 'X') ? 1 : 2;
    }
  }

  // Перевірка діагоналей
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    return (board[0][0] == 'X') ? 1 : 2;
  }
  if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
    return (board[0][2] == 'X') ? 1 : 2;
  }

  // Перевірка на нічию (якщо всі клітинки заповнені)
  bool full = true;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] != 'X' && board[i][j] != 'O') {
        full = false;
      }
    }
  }
  if (full) return 3; // Нічия

  return 0; // Нічого не сталося
}

// Функція для скидання гри
void resetGame() {
  // Перезапуск поля
  board[0][0] = '1'; board[0][1] = '2'; board[0][2] = '3';
  board[1][0] = '4'; board[1][1] = '5'; board[1][2] = '6';
  board[2][0] = '7'; board[2][1] = '8'; board[2][2] = '9';
  currentPlayer = 'X'; // Починає X
  Serial.println("G 0");
}

void setup() {
  // Налаштовуємо рядки як вихідні, стовпці як вхідні
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH); // Дефолтний стан
    pinMode(colPins[i], INPUT_PULLUP); // Підтягуючий резистор
  }
  Serial.begin(9600); // Налаштовуємо серійний зв'язок
}

void loop() {
  char pressedKey = scanKeypad();
  if (pressedKey != '\0' && pressedKey != lastKey) { // Якщо нова клавіша натиснута
    lastKey = pressedKey; // Зберігаємо натиснуту клавішу
    if (pressedKey >= '1' && pressedKey <= '9') {
      // Записуємо хід на ігровому полі
      int row = (pressedKey - '1') / 3;
      int col = (pressedKey - '1') % 3;
      if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentPlayer; // Оновлюємо поле
        // Надсилаємо поточного гравця ('X' чи 'O')
        Serial.print(currentPlayer); // Надсилаємо X чи O
        Serial.print(" ");
        Serial.println(pressedKey); // Надсилаємо номер клітинки
        // Перевірка на виграш або нічію
        int result = checkWin();
        if (result == 1) {
          Serial.println("Y 1"); // X виграв
          
          return;
        } else if (result == 2) {
          Serial.println("Y 2"); // O виграв
          
          return;
        } else if (result == 3) {
          Serial.println("Y 3"); // Нічия
          
          return;
        }
        // Перемикаємо гравця після ходу
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
      }
    } else if (pressedKey == 'D') {
      // Якщо натиснута 'D', скидаємо гру
      resetGame();
    }
  } else if (pressedKey == '\0') {
    lastKey = '\0'; // Скидаємо стан, якщо клавіша відпущена
  }
  delay(50); // Затримка для уникнення "дребезгу"
}

// Функція сканування кнопкової матриці
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
