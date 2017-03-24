#include "MCP23017-light.h"

// teensy 3.x/LC
#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
    #include "i2c_t3.h"
// ATtiny85
#elif defined(__AVR_ATtiny85__)
    #include <TinyWireM.h>
    #define Wire TinyWireM
// others
#else
    #include <Wire.h>
#endif

#define MCP23017_IODIRA     0x00
#define MCP23017_IPOLA      0x02
#define MCP23017_GPINTENA   0x04
#define MCP23017_DEFVALA    0x06
#define MCP23017_INTCONA    0x08
#define MCP23017_IOCONA     0x0A
#define MCP23017_GPPUA      0x0C
#define MCP23017_INTFA      0x0E
#define MCP23017_INTCAPA    0x10
#define MCP23017_GPIOA      0x12
#define MCP23017_OLATA      0x14

void MCP23017::begin(int addr) {
    begin(uint8_t(addr));
};

void MCP23017::begin(uint8_t addr) {
    i2cAddr = MCP23017_ADDR_BASE | addr;
};

void MCP23017::portMode(int port, uint8_t mode) {
    Wire.beginTransmission(i2cAddr);
    Wire.write(uint8_t(MCP23017_IODIRA | port));
    Wire.write(mode);
    Wire.endTransmission();
};

void MCP23017::portPullUps(int port, uint8_t mode) {
    Wire.beginTransmission(i2cAddr);
    Wire.write(uint8_t(MCP23017_GPPUA | port));
    Wire.write(mode);
    Wire.endTransmission();
};

uint8_t MCP23017::read(int port) {
    Wire.beginTransmission(i2cAddr);
    Wire.write(uint8_t(MCP23017_GPIOA | port));
    Wire.endTransmission();
    Wire.requestFrom(i2cAddr, uint8_t(1));
    return Wire.read();
};

uint16_t MCP23017::read() {
    Wire.beginTransmission(i2cAddr);
    Wire.write(uint8_t(MCP23017_GPIOA));
    Wire.endTransmission();
    Wire.requestFrom(i2cAddr, uint8_t(2));
    return uint16_t(Wire.read()) | (uint16_t(Wire.read()) << 8);
};
