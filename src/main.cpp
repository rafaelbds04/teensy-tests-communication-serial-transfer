#include <Arduino.h>
#include <vector>
#include <iostream>
#include <cstring>
#include "math.h"
#include "Wire.h"
#include "SerialTransfer.h"
// #include "Arduino.h"

struct MockPackage1
{
  uint8_t datagram_ID;     // 1 Byte - unsigned char   // Define type of next payload data
  uint32_t timestamp;      // 4 Byte - unsigned long
  float_t value;           // 4 Byte
} __attribute__((packed)); // attribute packed: Set smallest possible alignment, remove every padding.

struct MockPackage2
{
  uint8_t datagram_ID;     // 1 Byte - unsigned char   // Define type of next payload data
  uint32_t timestamp;      // 4 Byte - unsigned long
  uint8_t value;           // 1 Byte
  char padding[3];         // 3 Bytes
} __attribute__((packed)); // attribute packed: Set smallest possible alignment, remove every padding.

class Buffer
{
public:
  Buffer(size_t capacity, size_t datasize) : capacity_(capacity), size_(0), datasize_(datasize) {}

  template <typename T>
  void addItem(const T &item)
  {
    // Serialize the item and append it to the buffer
    const char *itemBytes = reinterpret_cast<const char *>(&item);
    buffer.insert(buffer.end(), itemBytes, itemBytes + sizeof(T));
    size_++;
  }

  template <typename T>
  T getItem(size_t index) const
  {
    // Deserialize the item from the buffer
    T item;
    std::memcpy(&item, &buffer[index], sizeof(T));
    return item;
  }

  bool isFull() const
  {
    // Implement based on your specific requirements
    return ((size_ * datasize_) == capacity_); // Multiply size_ to the struct size
  }

  bool isEmpty() const
  {
    return buffer.empty();
  }

  void clearBuffer()
  {
    buffer.clear();
  }

  // void sendViaSerial() const {
  //     if (isFull()) {
  //         SerialTransfer myTransfer;  // Instantiate a SerialTransfer object

  //         // Start the serial communication with a specific baud rate
  //         Serial.begin(115200);

  //         // Wait for the serial port to be ready
  //         while (!Serial);

  //         // Configure the SerialTransfer object with the Serial port
  //         myTransfer.begin(Serial);

  //         // Send the data in the buffer via SerialTransfer
  //         if (!buffer.empty()) {
  //             myTransfer.sendDatum(buffer.buffer[0], 243);
  //         }

  //         // Optionally, wait for the transmission to complete
  //         while (!myTransfer.available());

  //         // Close the serial port
  //         Serial.end();
  //     }
  // }
  std::vector<char> buffer;
  
private:
  size_t capacity_;
  size_t size_;
  size_t datasize_;
};

SerialTransfer myTransfer;
void setup()
{

  Serial.begin(115200);
  myTransfer.begin(Serial);
  Buffer buffer(243, 9);

  delay(5000);

  for (uint8_t i = 1; i < 10; i++)
  {
    MockPackage1 p;
    p = {25, 200, 1000.0F + i};
    buffer.addItem(p);
  }

  for (uint8_t i = 10; i < 28; i++)
  {
    MockPackage2 p;
    p = {1, 300, 1};
    buffer.addItem(p);
  }

  // Serial.println();
  // MockPackage1 retrievedPackage1 = buffer.getItem<MockPackage1>(0);
  // Serial.print("Retrieved Package:");
  // Serial.print(retrievedPackage1.datagram_ID);
  // Serial.print(" , Timestamp:");
  // Serial.print(retrievedPackage1.timestamp);
  // Serial.print(" , Value:");
  // Serial.println(retrievedPackage1.value);

  // std::cout << "Retrieved Package: " << retrievedPackage1.datagram_ID << ", Value: " << retrievedPackage1.value << std::endl;
  // printf("%f\n", retrievedPackage1.value);

  // MockPackage2 retrievedPackage2 = buffer.getItem<MockPackage2>(234);
  // std::cout << "Retrieved Package: " << retrievedPackage2.datagram_ID << ", Value: " << retrievedPackage2.value << std::endl;
  // printf("%i\n", retrievedPackage2.value);

  // Serial.print("Retrieved Package:");
  // Serial.print(retrievedPackage2.datagram_ID);
  // Serial.print(" , Timestamp:");
  // Serial.print(retrievedPackage2.timestamp);
  // Serial.print(" , Value:");
  // Serial.println(retrievedPackage2.value);

  // Serial.print("isFull: ");
  // Serial.println(buffer.isFull());

  // auto exitBuffer;
  // std::memcpy(&exitBuffer, &buffer.buffer[0], 243);
  uint8_t size = myTransfer.sendDatum(buffer.buffer[0], 243);
  // uint8_t size = myTransfer.sendDatum(buffer.buffer.data(), 243);
  // Serial.println();
  // Serial.println(size);
};

void loop() {};