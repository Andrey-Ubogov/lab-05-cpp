#pragma once
#include "BaseDevice.hpp"
#include "IHeatingMode.hpp"

class SmartThermostat final : public BaseDevice {
private:
    std::unique_ptr<IHeatingMode> m_mode; // Объект поведения

public:
    SmartThermostat(const std::string& name, int power, std::shared_ptr<std::string> roomName, std::unique_ptr<IHeatingMode> mode);

    void SetMode(std::unique_ptr<IHeatingMode> newMode);

    std::string GetType() const override { return "Термостат"; }
    std::string Describe() const override;
    std::unique_ptr<BaseDevice> Clone() const override;
};