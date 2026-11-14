#pragma once
#include <stdexcept>
#include <string>

// Наследуемся от std::runtime_error, чтобы его можно было поймать как std::exception.
class DeviceBrokenException : public std::runtime_error {
public:
    explicit DeviceBrokenException(const std::string& deviceName)
        : std::runtime_error("Устройство '" + deviceName + "' сломано! Нельзя включить.") {}
};