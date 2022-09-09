#include <Arduino.h>
#include <stdint.h>
#include "Surtidor.h"
#include "Comander.h"

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);    
}

void loop() {
    while(Serial1.available() == 0); // Se queda esperando a recibir el otro byte
    uint8_t incomingByte = Serial1.read();

    Serial.print("Recibi el byte: ");
    Serial.println(incomingByte, BIN);

    if(isStatus(incomingByte)){
        Serial.println("Era status");

        uint8_t statusByte = incomingByte;

        while(Serial1.available() == 0); // Se queda esperando a recibir el otro byte

        incomingByte = Serial1.read();

        Serial.print("Recibi el segundo byte: ");
        Serial.println(incomingByte, BIN);

        if(isData(incomingByte)){
            Serial.println("Era data");

            uint8_t command = getCommand(statusByte);
            uint8_t subcommand = getSubCommand(statusByte); 
            uint8_t data = getData(incomingByte);

            // Proceso el comando
            Serial.print("Comando: ");
            Serial.print(command, BIN);
            Serial.print(" Subcomando: ");
            Serial.print(subcommand, BIN);
            Serial.print(" Data: ");
            Serial.println(data, BIN);
        }
    }
}
