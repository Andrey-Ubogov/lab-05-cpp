#include "SmartLamp.hpp"

SmartLamp::SmartLamp(const std::string& name, int power, std::shared_ptr<std::string> roomName, int brightness)
    : BaseDevice(name, power, roomName), m_brightness(brightness) {
    std::cout << "[SmartLamp] Создана лампа: " << GetName() << std::endl;
}

SmartLamp::SmartLamp(const SmartLamp& other)
    : BaseDevice(other), m_brightness(other.m_brightness) {
    std::cout << "[SmartLamp] Копирование лампы" << std::endl;
}

std::string SmartLamp::Describe() const {
    return BaseDevice::Describe() + ", яркость: " + std::to_string(m_brightness) + "%";
}

void SmartLamp::ConnectToWiFi() {
    m_isConnected = true;
    std::cout << "  Лампа '" << GetName() << "' подключена к Wi-Fi." << std::endl;
}

void SmartLamp::DisconnectFromWiFi() {
    m_isConnected = false;
    std::cout << "  Лампа '" << GetName() << "' отключена от Wi-Fi." << std::endl;
}

void SmartLamp::SetBrightness(int brightness) {
    if (brightness < 0 || brightness > 100) {
        std::cout << "  Ошибка: Яркость должна быть от 0 до 100." << std::endl;
        return;
    }
    m_brightness = brightness;
    std::cout << "  Яркость лампы '" << GetName() << "' изменена на " << m_brightness << "%." << std::endl;
}