# Мінімальна версія CMake
cmake_minimum_required(VERSION 3.10)

# Назва проєкту
project(TicTacToe CXX)

# Вказуємо стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указуємо директорії з заголовковими файлами
include_directories(include)

# Додаємо вихідні файли для основної програми
set(SRC_FILES
    Receiver.cpp
    SerialPort.cpp
)

# Бінарник основної програми
add_executable(tictactoe ${SRC_FILES})

# Тести
set(TEST_FILES
    test.cpp
    SerialPort.cpp
)

# Бінарник для тестів
add_executable(tests ${TEST_FILES})

# Підключаємо бібліотеку doctest (вбудована у файл тесту)
target_include_directories(tests PRIVATE include)
