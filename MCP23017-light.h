#ifndef MCP23017_LIGHT_H
    #define MCP23017_LIGHT_H

    #define MCP23017_ADDR_BASE 0x20

    #define MCP23017_PORTA 0
    #define MCP23017_PORTB 1

    #include <stdint.h>

    class MCP23017 {
    public:
        void begin(uint8_t addr);
        void begin(int addr);
        void portMode(int port, uint8_t mode);
        void portPullUps(int port, uint8_t mode);
        uint8_t read(int port);
        uint16_t read();
        void write(int port, uint8_t value);
        void write(uint16_t value);
    private:
        uint8_t i2cAddr;
    };

#endif
