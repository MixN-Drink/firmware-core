#include <Arduino.h>
#include <stdint.h>
#include "Surtidor.h"
#include "Comander.h"

void checkIncomingCommand(void);

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);
    motoresInit();
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    checkIncomingCommand();
    procesarMotores();
}

void checkIncomingCommand(void){
    static uint8_t statusByte, dataByte;
    static bool receiving = false, complete = false;

    while(Serial.available()){
        uint8_t incomingByte = Serial.read();
        Serial.print("Recibi el byte: ");
        Serial.println(incomingByte, BIN);

        if(isStatus(incomingByte)){ // Inicio del comando
            receiving = true;
            complete = false;
            statusByte = incomingByte;
        } else if(isData(incomingByte) && receiving){
            receiving = false;
            complete = true;
            dataByte = incomingByte;
        }
    }

    if(complete){
        complete = false;

        uint8_t command = getCommand(statusByte);
        uint8_t subcommand = getSubCommand(statusByte); 
        uint8_t data = getData(dataByte);

        // Proceso el comando
        Serial.print("Comando: ");
        Serial.print(command, BIN);
        Serial.print(" Subcomando: ");
        Serial.print(subcommand, BIN);
        Serial.print(" Data: ");
        Serial.println(data, BIN);

        switch(command){
            case COMMAND_PUMP:{
                    bool err = surtir(subcommand, data);
                    if(err){
                        Serial.println("Error al procesar procesar el comando surtir");
                    }
                }
                break;
            case COMMAND_LED:{
                    digitalWrite(LED_BUILTIN, data);
                }
                break;           
            case COMMAND_STOP_PUMP:{
                    detenerMotor();
                }
                break;
            case COMMAND_CALIBRATION:{
                if(subcommand==0){
                    iniciarCalibracion();
                }    
                else{
                    detenerCalibracion();
                    
                }
            }
            break;

        }
    }
}