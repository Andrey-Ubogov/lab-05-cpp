#pragma once
#include <string>
#include <iostream>

class IConnectable {
public:
    virtual ~IConnectable() = default;

    virtual void ConnectToWiFi() = 0;
    virtual void DisconnectFromWiFi() = 0;
};