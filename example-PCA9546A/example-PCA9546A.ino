#include "PCA9547.h"

PCA9546A i2cSelect;
unsigned int ch = 0;

void setup()
{
    Serial.begin(115200);
    i2cSelect.begin(); // default addr : 0x70
    // i2cSelect.begin(0x74); // or set your addr
    Serial.print("status = ");
    Serial.println(i2cSelect.getStatus());
    delay(100);
}

void loop()
{
    Serial.print("set ch to  : ");
    Serial.println(ch % 4, HEX);
    i2cSelect.enable(ch % 4);

    Serial.print("current ch : ");
    Serial.println(i2cSelect.channel(), HEX);

    Serial.print("status = ");
    Serial.println(i2cSelect.getStatus());

    ++ch;
    delay(1000);
}
