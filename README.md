# PCA9547

Arduino library for [PCA9547](https://www.nxp.com/jp/products/analog/interfaces/ic-bus/ic-multiplexers-switches/8-channel-i2c-bus-multiplexer-with-reset:PCA9547) (8-channel I2C-bus multiplexer with reset) and [PCA9546A](https://www.nxp.com/jp/products/analog/interfaces/ic-bus/ic-multiplexers-switches/4-channel-i2c-bus-switch-with-reset:PCA9546A) (4-channel I2C-bus switch with reset)

## Usage

``` C++
#include "PCA9547.h"
PCA9547 i2cSelect;

unsigned int ch = 0;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    i2cSelect.attach(Wire); // default addr : 0x70
    // i2cSelect.attach(Wire, 0x74); // or set your addr
    delay(100);
}

void loop()
{
    i2cSelect.enable(ch % 8); // write to IC
    Serial.print("current ch : ");
    Serial.println(i2cSelect.channel(), HEX); // read from IC
    ++ch;
    delay(1000);
}
```

### Functions

``` C++
void attach(TwoWire& w, uint8_t addr = I2C_ADDR_DEFAULT);
uint8_t channel();
void enable(const uint8_t ch);
void disable();
void setAddress(const uint8_t addr);
void setAddress(const bool A0, const bool A1, const bool A2);
uint8_t getStatus();
// 0 : success
// 1 : data too long
// 2 : NACK on transmit of address
// 3 : NACK on transmit of data
// 4 : other
```

## License

MIT
