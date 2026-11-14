#pragma once
#include "IHeatingMode.hpp"
#include <string>

// Режим "Экономия"
class EconomyMode : public IHeatingMode {
public:
    int GetTargetTemperature() const override { return 18; }
    std::string GetModeName() const override { return "Экономия"; }
};

// Режим "Комфорт"
class ComfortMode : public IHeatingMode {
public:
    int GetTargetTemperature() const override { return 23; }
    std::string GetModeName() const override { return "Комфорт"; }
};