#include "PCA9547.h"

PCA9547 i2cSelect;
unsigned int ch = 0;

void setup()
{
    Serial.begin(115200);
    i2cSelect.begin(); // default addr : 0x70
    // i2cSelect.begin(0x74); // or set your addr
    delay(100);
}

void loop()
{
    i2cSelect.enable(ch % 8);
    Serial.print("current ch : ");
    Serial.println(i2cSelect.channel(), HEX);
    ++ch;
    delay(1000);
}
