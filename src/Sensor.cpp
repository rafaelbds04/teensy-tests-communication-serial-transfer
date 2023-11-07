#include "Arduino.h"

enum SensorID : uint8_t { 
    INIT,
    ADS1256_PT_01,
    ADS1256_PT_T1,
    ADS1256_PT_T2,
    ADS1256_PT_C1,
    ADS1256_PT_N1,
    HX711_WT_01,
    HX711_WT_T1,
    ADS1256_WT_C1,
    MAX31855_TT_O1,
    MAX31855_TT_T1,
    MAX31855_TT_C1,
    MAX31855_TT_C2,
    MAX31855_TT_C3,
    MAX31855_TT_C4,
    THERMISTOR_TR_T1,
    THERMISTOR_TR_C1,
    VALVE_STATE_SPV_T1,
    VALVE_STATE_SPV_O1,
    VALVE_STATE_SPV_M1,
    INA219_VOLTAGE_DL,
    INA219_CURRENT_DL,
    INA219_VOLTAGE_DHE,
    INA219_CURRENT_DHE
};

struct Package
{
    uint32_t timestamp;
    SensorID sensorId;
};

struct FloatPayload : Package
{
    float_t value;
};

struct Uint8Payload : Package
{
    uint8_t value;
};

struct Uint16Payload : Package
{
    uint16_t value;
};

struct Uint32Payload : Package
{
    uint32_t value;
};

struct Uint64Payload : Package
{
    uint64_t value;
};

typedef FloatPayload MAX31855Packet;
typedef FloatPayload ThermistorPackage;

class MAX31855Wrapper
{
private:
    Package lastPackage[2] = { Uint32Payload{}, Uint64Payload{ }};
    // MAX31855Packet lastPackage;
    /* data */
public:
    MAX31855Packet getLastPackage();
};