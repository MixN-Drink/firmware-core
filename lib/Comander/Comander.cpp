#include "Comander.h"

bool isStatus(uint8_t inByte){
    return (inByte & TYPE_MASK) >> TYPE_SHIFT;
}
bool isData(uint8_t inByte){
    return !isStatus(inByte);
}
uint8_t getCommand(uint8_t inByte){
    return inByte & COMMAND_MASK;
}
uint8_t getSubCommand(uint8_t inByte){
    return inByte & SUBCOMMAND_MASK >> SUBCOMMAND_SHIFT;
}
uint8_t getData(uint8_t inByte){
    return inByte & DATA_MASK;
}