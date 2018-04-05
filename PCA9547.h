#pragma once
#ifndef PCA9547_H
#define PCA9547_H

#include <Wire.h>

class PCA9547
{
    static const uint8_t I2C_ADDR_DEFAULT = 0x70;
    static const uint8_t I2C_ADDR_MAX = 0x77;

    static const uint8_t CHANNEL_ENABLE_BIT = 0x08;
    static const uint8_t CHANNEL_MASK = 0x07;
    static const uint8_t CHANNEL_DISABLED = 0xFF;

public:

    void begin(uint8_t addr = I2C_ADDR_DEFAULT)
    {
        Wire.begin();
        addr_ = addr;
    }

    uint8_t channel() const
    {
        if (Wire.requestFrom((uint8_t)addr_, (uint8_t)1))
        {
            uint8_t data = Wire.read();
            Serial.println(data, HEX);
            if (data & CHANNEL_ENABLE_BIT) return (CHANNEL_MASK & data);
        }
        else
        {
            Serial.println("No data");
        }
        return 0xFF;
    }

    void enable(const uint8_t ch)
    {
        if (ch > 7) disable();
        else
        {
            Wire.beginTransmission(addr_);
            Wire.write(CHANNEL_ENABLE_BIT | ch);
            status_ = Wire.endTransmission();
        }
    }

    void disable()
    {
        Wire.beginTransmission(addr_);
        Wire.write(0x00);
        status_ = Wire.endTransmission();
    }

    void setAddress(const uint8_t addr)
    {
        if (addr < I2C_ADDR_DEFAULT || addr > I2C_ADDR_MAX)
            addr_ = I2C_ADDR_DEFAULT;
        else
            addr_ = addr;
    }

    void setAddress(const bool A0, const bool A1, const bool A2)
    {
        addr_ = I2C_ADDR_DEFAULT;
        if (A2) addr_ |= 0x04;
        if (A1) addr_ |= 0x02;
        if (A0) addr_ |= 0x01;
    }

    // 0 : success
    // 1 : data too long
    // 2 : NACK on transmit of address
    // 3 : NACK on transmit of data
    // 4 : other
    uint8_t getStatus() const { return status_; }

    void printStatus() const
    {
        Serial.print("current I2C status : ");
        Serial.println(status_);
    }

private:

    uint8_t addr_;
    uint8_t status_;
};

#endif // PCA9547_H
