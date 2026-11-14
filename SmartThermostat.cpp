#include "SmartThermostat.hpp"
#include "HeatingModes.hpp"

SmartThermostat::SmartThermostat(const std::string& name, int power, std::shared_ptr<std::string> roomName, std::unique_ptr<IHeatingMode> mode)
    : BaseDevice(name, power, roomName), m_mode(std::move(mode)) {
    std::cout << "[SmartThermostat] Создан термостат: " << GetName() << std::endl;
}

void SmartThermostat::SetMode(std::unique_ptr<IHeatingMode> newMode) {
    m_mode = std::move(newMode);
    std::cout << "  Термостат '" << GetName() << "' переключен в режим: " << m_mode->GetModeName() << std::endl;
}

std::string SmartThermostat::Describe() const {
    return "Термостат '" + GetName() + "': режим '" + m_mode->GetModeName() +
        "', целевая температура " + std::to_string(m_mode->GetTargetTemperature()) + " C";
}

// Глубокая копия термостата
std::unique_ptr<BaseDevice> SmartThermostat::Clone() const {
    // Создаем копию режима (предполагаем, что у нас только 2 режима, выбираем по имени)
    std::unique_ptr<IHeatingMode> modeCopy;
    if (m_mode->GetModeName() == "Экономия") {
        modeCopy = std::make_unique<EconomyMode>();
    }
    else {
        modeCopy = std::make_unique<ComfortMode>();
    }
    return std::make_unique<SmartThermostat>(GetName(), GetPower(), std::make_shared<std::string>("Комната"), std::move(modeCopy));
}