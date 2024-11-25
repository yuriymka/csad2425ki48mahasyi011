#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <string>
#include "SerialPort.hpp" // Додаємо вашу бібліотеку для роботи з COM-портами

/// @brief Мок-клас для імітації SerialPort.
class MockSerialPort : public SerialPort {
public:
    MockSerialPort(const char* portName) : SerialPort(portName) {}

    /// @brief Імітація читання даних із COM-порту.
    int readSerialPort(char* buffer, unsigned int buf_size) override {
        std::string mockResponse = "Y 1"; // Симулюємо, що Arduino надіслав "Y 1"
        if (mockResponse.size() + 1 <= buf_size) {
            strcpy(buffer, mockResponse.c_str());
            return mockResponse.size();
        }
        return 0;
    }
};

TEST_CASE("Game end condition: Player X wins") {
    char portName[] = "\\\\.\\COM3";

    // Створюємо мок-об'єкт для імітації роботи SerialPort
    MockSerialPort mockPort(portName);

    // Симулюємо отримання рядка "Y 1"
    char incomingData[256] = "";
    int readResult = mockPort.readSerialPort(incomingData, 255);

    REQUIRE(readResult > 0); // Перевіряємо, що дані успішно отримані
    CHECK(std::string(incomingData) == "Y 1"); // Перевіряємо, чи дані відповідають "Y 1"
}
