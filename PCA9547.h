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

    void attatch(TwoWire& w) { wire = &w; addr_ = I2C_ADDR_DEFAULT; }

    virtual uint8_t channel() const
    {
        if (wire->requestFrom((uint8_t)addr_, (uint8_t)1))
        {
            uint8_t data = wire->read();
            if (data & CHANNEL_ENABLE_BIT) return (CHANNEL_MASK & data);
            else Serial.println("disabled");
        }
        else
        {
            Serial.println("no data");
        }
        return 0xFF;
    }

    virtual void enable(const uint8_t ch)
    {
        if (ch > 7) disable();
        else
        {
            wire->beginTransmission(addr_);
            wire->write(CHANNEL_ENABLE_BIT | ch);
            status_ = wire->endTransmission();
        }
    }

    void disable()
    {
        wire->beginTransmission(addr_);
        wire->write(0x00);
        status_ = wire->endTransmission();
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

protected:

    TwoWire* wire;
    uint8_t addr_;
    uint8_t status_;
};


class PCA9546A : public PCA9547
{
public:
    virtual ~PCA9546A() {}

    virtual uint8_t channel() const override
    {
        if (wire->requestFrom((uint8_t)addr_, (uint8_t)1))
        {
            uint8_t data = wire->read();
            if (data & 0x01) return 0;
            if (data & 0x02) return 1;
            if (data & 0x04) return 2;
            if (data & 0x08) return 3;
            Serial.println("disabled");
        }
        else
        {
            Serial.println("no data");
        }
        return 0xFF;
    }

    virtual void enable(const uint8_t ch) override
    {
        if (ch > 3 ) disable();
        else
        {
            wire->beginTransmission(addr_);
            wire->write(0x01 << ch);
            status_ = wire->endTransmission();
        }
    }
};

#endif // PCA9547_H
