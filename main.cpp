#include <iostream>
#include <memory>
#include <vector>
#include <Windows.h>

#include "BaseDevice.hpp"
#include "SmartLamp.hpp"
#include "SmartThermostat.hpp"
#include "IConnectable.hpp"
#include "HeatingModes.hpp"
#include "Exceptions.hpp"

// Функция, работающая через ИНТЕРФЕЙС (не знает о лампах/термостатах)
void ConnectDeviceToNetwork(IConnectable& device) {
    std::cout << "Подключение к сети..." << std::endl;
    device.ConnectToWiFi();
}

// Функция, использующая dynamic_cast
void TryToConnect(BaseDevice* device) {
    // Пытаемся привести к IConnectable
    if (auto* connectable = dynamic_cast<IConnectable*>(device)) {
        connectable->ConnectToWiFi();
    }
    else {
        std::cout << "  Устройство '" << device->GetName() << "' не поддерживает Wi-Fi." << std::endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "Russian");

    std::cout << "========== ЛР 5. Полиморфизм ==========\n" << std::endl;
    auto room = std::make_shared<std::string>("Гостиная");

    // 1. Раннее и позднее связывание
    std::cout << "--- 1. Раннее и позднее связывание ---" << std::endl;
    std::unique_ptr<BaseDevice> baseLamp = std::make_unique<SmartLamp>("Лампа 1", 10, room);

    // Раннее связывание: вызовется BaseDevice::GetCategory()
    std::cout << "Раннее связывание (GetCategory): " << baseLamp->GetCategory() << std::endl;

    // Позднее связывание: вызовется SmartLamp::Describe()
    std::cout << "Позднее связывание (Describe): " << baseLamp->Describe() << std::endl;

    // 2. dynamic_cast и интерфейсы
    std::cout << "\n--- 2. dynamic_cast и работа через интерфейс ---" << std::endl;
    auto lamp = std::make_unique<SmartLamp>("Умная лампа", 10, room);
    auto thermostat = std::make_unique<SmartThermostat>("Термостат", 15, room, std::make_unique<ComfortMode>());

    TryToConnect(lamp.get());      // Сработает dynamic_cast (лампа умеет Wi-Fi)
    TryToConnect(thermostat.get()); // Не сработает (термостат не наследует IConnectable)

    // Работа через интерфейс напрямую
    ConnectDeviceToNetwork(*lamp);

    // 3. Конфигурирование поведения
    std::cout << "\n--- 3. Конфигурирование поведения ---" << std::endl;
    std::cout << "До смены режима: " << thermostat->Describe() << std::endl;
    thermostat->SetMode(std::make_unique<EconomyMode>()); // Динамическое конфигурирование
    std::cout << "После смены режима: " << thermostat->Describe() << std::endl;

    // 4. Исключения
    std::cout << "\n--- 4. Исключения ---" << std::endl;
    try {
        baseLamp->TurnOn(); // Успешно
        baseLamp->Break();  // Ломаем
        baseLamp->TurnOn(); // Бросает исключение!
    }
    catch (const DeviceBrokenException& ex) { // Ловим частное исключение
        std::cout << "Поймано исключение: " << ex.what() << std::endl;
    }
    catch (const std::exception& ex) { // Ловим общее (если вдруг что-то другое)
        std::cout << "Поймано общее исключение: " << ex.what() << std::endl;
    }

    std::cout << "\n========== КОНЕЦ ==========" << std::endl;
    return 0;
}