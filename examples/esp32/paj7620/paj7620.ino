/**
 * Example sketch from https://www.esp32learning.com/code/paj7620-gesture-sensor-and-esp32.php
 * 
 * Requires library: https://www.elecrow.com/wiki/images/7/72/Paj7620.zip
 * Sketch -> Include Library from Zip
 */


#include <Wire.h>
#include "paj7620.h"

void setup()
{
Serial.begin(115200);
paj7620Init();
}

void loop()
{
uint8_t data = 0; // Read Bank_0_Reg_0x43/0x44 for gesture result.

paj7620ReadReg(0x43, 1, &data);

if (data == GES_UP_FLAG)
{
Serial.println("GES_UP_FLAG !");
}

if (data == GES_DOWN_FLAG)
{
Serial.println("GES_DOWN_FLAG !");
}

if(data == GES_FORWARD_FLAG)
{
Serial.println("GES_FORWARD_FLAG !");
}

if(data == GES_BACKWARD_FLAG)
{
Serial.println("GES_BACKWARD_FLAG !");
}

if(data == GES_RIGHT_FLAG)
{
Serial.println("GES_RIGHT_FLAG !");
}

if(data ==GES_LEFT_FLAG)
{
Serial.println("GES_LEFT_FLAG !");
}

}
