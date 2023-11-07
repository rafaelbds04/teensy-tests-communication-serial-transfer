#include <Arduino.h>
// #include "Sensor.cpp"
#include "Wire.h"
#include "SerialTransfer.h"

SerialTransfer myTransfer;
uint32_t nextUpdate, timeToComplete;

struct SensorPackage
{
  uint8_t datagram_ID; //     // Define type of next payload data // 1 - unsigned char
  uint32_t timestamp;   // 4 - unsigned long
  float_t value; // 4
}__attribute__((packed)); //attribute packed: Set smallest possible alignment.

/*
|     timestamp     | 4B
|  id |    padd     | 1B + 3B -> Normal alligment
|      value        | 4B
*/

/*
|     timestamp     | padd | 4B + 1B -> Possible normal alligment
|  id  |       value       | 5B
*/

/*
|     timestamp     |  id  |       value       | 9B -> Smallest possible alligment
*/
// https://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/

typedef SensorPackage MAX31855Packet;

MAX31855Packet buffer[2];

void setup()
{
  buffer[0] = {1U, 165614565, 1561.50F};
  buffer[1] = {1U, 101010, 65.50F};
  Serial.begin(115200);
  myTransfer.begin(Serial);
  nextUpdate = micros();

  // y = 4.5;
}

void loop()
{

  // micros()
  if (micros() >= nextUpdate)
  {
    // Serial.println(sizeof(SensorPackage));
    timeToComplete = micros();
    uint8_t size = myTransfer.sendDatum(buffer);
    // timeToComplete = micros() - timeToComplete;
    // Serial.print("\nTotal:");
    // Serial.print(timeToComplete);
    // Serial.print(" : size: ");
    // Serial.print(sizeof(SensorPackage));
    // Serial.print(" : sended size: ");
    // Serial.println(size);
    nextUpdate = micros() + 1000000 ;
  }
  // delay(100);
}