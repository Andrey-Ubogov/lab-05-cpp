#pragma once

// Объект поведения
class IHeatingMode {
public:
    virtual ~IHeatingMode() = default;
    virtual int GetTargetTemperature() const = 0;
    virtual std::string GetModeName() const = 0;
};