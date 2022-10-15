#include <Arduino.h>
#include <stdint.h>
#include "Surtidor.h"
#include "Comander.h"

#define USB Serial
#define ESP12 Serial3

void checkIncomingCommand(void);

void setup() {
    USB.begin(9600);
    ESP12.begin(9600);
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

    while(ESP12.available()){
        uint8_t incomingByte = ESP12.read();
        USB.print("Recibi el byte: ");
        USB.println(incomingByte, BIN);

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
        USB.print("Comando: ");
        USB.print(command, BIN);
        USB.print(" Subcomando: ");
        USB.print(subcommand, BIN);
        USB.print(" Data: ");
        USB.println(data, BIN);

        switch(command){
            case COMMAND_PUMP:{
                    bool err = surtir(subcommand, data);
                    if(err){
                        USB.println("Error al procesar procesar el comando surtir");
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