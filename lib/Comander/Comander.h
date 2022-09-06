#include <stdint.h>

#define TYPE_MASK        0b10000000
#define TYPE_SHIFT       7
#define COMMAND_MASK     0b00001111
#define SUBCOMMAND_MASK  0b01110000
#define SUBCOMMAND_SHIFT 4
#define DATA_MASK        0b01111111

bool isStatus(uint8_t inByte);
bool isData(uint8_t inByte);
uint8_t getCommand(uint8_t inByte);
uint8_t getSubCommand(uint8_t inByte);
uint8_t getData(uint8_t inByte);