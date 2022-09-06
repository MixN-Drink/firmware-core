#include <Arduino.h>
#include <stdint.h>
#include "Surtidor.h"
#include "Comander.h"

void setup() {
}

void loop() {
    uint8_t incomingByte = Serial.read();

    if(isStatus(incomingByte)){
        uint8_t command = getCommand(incomingByte);
        uint8_t subcommand = getSubCommand(incomingByte);

        incomingByte = Serial.read();

        if(isData(incomingByte)){
            uint8_t data = getData(incomingByte);

            

        }
    }
}
