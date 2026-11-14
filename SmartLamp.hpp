#pragma once
#include "BaseDevice.hpp"
#include "IConnectable.hpp"

class SmartLamp : public BaseDevice, public IConnectable {
private:
    int m_brightness;
    bool m_isConnected;

public:
    SmartLamp(const std::string& name, int power, std::shared_ptr<std::string> roomName, int brightness = 100);
    SmartLamp(const SmartLamp& other);

    // Переопределение метода базы
    std::string GetType() const override { return "Умная лампа"; }

    // Скрываем невиртуальный метод базы (для демонстрации)
    std::string GetCategory() const { return "Осветительный прибор"; }

    std::string Describe() const override;
    std::unique_ptr<BaseDevice> Clone() const override { return std::make_unique<SmartLamp>(*this); }

    void SetBrightness(int brightness);

    // Реализация контракта IConnectable
    void ConnectToWiFi() override;
    void DisconnectFromWiFi() override;
};