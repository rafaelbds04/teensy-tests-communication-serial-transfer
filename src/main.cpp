#include <Arduino.h>
#include "Types.h"
#include "Wire.h"
#include "SerialTransfer.h"
#include "RingBufCPP.h"

SerialTransfer myTransfer;
uint32_t nextUpdate, timeToComplete;

RingBufCPP<Package, 27> packageBuffer;

// MAX31855Packet buffer[27];

void setup()
{
  for (uint16_t i = 0; i < 27; i++)
  {
    FloatPayload p;
    p.datagramID = Datagram::ADS1256_PT_01;
    p.timestamp = millis() + i;
    p.value = 1000.0F + i;
    // FloatPayload p  = {i, millis(), 1000.0F + i };
    // {i, millis(), 1000.0F + i }
    packageBuffer.add(p);
  }

  // for (uint16_t i = 10; i < 27; i++)
  // {
  //   Uint8Payload p;
  //   p.datagramID = Datagram::ADS1256_PT_01;
  //   p.timestamp = millis() + i;
  //   // p.value = 1000.0F + i;
  //   p.value = i;
  //   // FloatPayload p  = {i, millis(), 1000.0F + i };
  //   // {i, millis(), 1000.0F + i }
  //   packageBuffer.add(p);
  // }

  Serial.begin(115200);
  myTransfer.begin(Serial);
  nextUpdate = micros();
  delay(5000);

  // y = 4.5;
}

//   RingBufCPP<int, 5> q;
//     int tmp = 12;
//     //q.add(tmp);

//  for (uint16_t i=0; i< 100; i++) {
//         int tmp = random();

//         if (q.add(tmp)) {
//             printf("Added %d\n", tmp);
//         }
//         else {
//             q.pull(&tmp);
//             break;
//         }



void loop()
{

  // micros()
  if (micros() >= nextUpdate)
  {

    // Serial.println(sizeof(SensorPackage));
    // timeToComplete = micros();

    // for (size_t i = 0; i < 1; i++)
    // {
    //   uint8_t size = myTransfer.sendDatum(packageBuffer);
    //    Serial.println(size);
    // }

    // timeToComplete = micros() - timeToComplete;
    // Serial.print("\nTotal:");
    // Serial.print(timeToComplete);
    Serial.print(" : size: ");
    Serial.println(sizeof(packageBuffer));

    Serial.print(" : numElements: ");
    Serial.println(packageBuffer.numElements());

    Serial.print(" : isFull: ");
    Serial.println(packageBuffer.isFull());

    packageBuffer.pull(&);

    // Serial.print(" : sended size: ");
    // Serial.println(size);
    nextUpdate = micros() + 1000000;
    // nextUpdate = micros() + 250000;
  }
  // delay(100);
}